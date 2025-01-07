#ifndef OUR_AVL_TREE_HPP
#define OUR_AVL_TREE_HPP
#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

template<typename K, typename V, typename Compare = std::less<K> >
class AVLMultiMap {
 private:
  class Node {
   public:
    K key;
    std::set<V> vals;
    int height;
    Node * left;
    Node * right;
    int getLeftChildHeight() const noexcept {
      return left == nullptr ? -1 : left->height;
    }
    int getRightChildHeight() const noexcept {
      return right == nullptr ? -1 : right->height;
    }
    void updateHeight() noexcept {
      height = 1 + std::max(getLeftChildHeight(), getRightChildHeight());
    }
    Node(const K & key_, const V & val_) :
        key(key_), vals(), height(0), left(nullptr), right(nullptr) {
      vals.insert(val_);
    }
    Node(const K & key_, const std::set<V> & vals_, Node * ileft, Node * iright) :
        key(key_), vals(vals_), left(ileft), right(iright) {
      updateHeight();
    }

    int getBalanceDiff() const noexcept {
      return getLeftChildHeight() - getRightChildHeight();
    }
    bool tooMuchOnLeft() const noexcept { return getBalanceDiff() > 1; }
    bool tooMuchOnRight() const noexcept { return getBalanceDiff() < -1; }
    bool isLeftSideDeeper() const noexcept { return getBalanceDiff() >= 0; }
    bool isRightSideDeeper() const noexcept { return getBalanceDiff() <= 0; }
  };
  Node * root;
  Compare cmp;

  Node * leftRotate(Node * curr) noexcept {
    Node * node = curr->right;
    curr->right = node->left;
    node->left = curr;
    curr->updateHeight();
    node->updateHeight();
    return node;
  }
  Node * rightRotate(Node * curr) noexcept {
    Node * node = curr->left;
    curr->left = node->right;
    node->right = curr;
    curr->updateHeight();
    node->updateHeight();
    return node;
  }
  Node * leftRightRotate(Node * curr) noexcept {
    curr->left = leftRotate(curr->left);
    return rightRotate(curr);
  }
  Node * rightLeftRotate(Node * curr) noexcept {
    curr->right = rightRotate(curr->right);
    return leftRotate(curr);
  }
  Node * copyHelper(const Node * curr) const {
    if (curr == nullptr) {
      return nullptr;
    }
    return new Node(
        curr->key, curr->vals, copyHelper(curr->left), copyHelper(curr->right));
  }

 public:
  AVLMultiMap()
      noexcept(noexcept(std::is_nothrow_default_constructible<Compare>::value)) :
      root(nullptr), cmp() {}
  AVLMultiMap(const AVLMultiMap & rhs) : root(copyHelper(rhs.root)), cmp(rhs.cmp) {}
  void add(const K & key, const V & val) { root = insertHelper(root, key, val); }
  void remove(const K & key, const V & val) { root = deleteHelper(root, key, val); }
  ~AVLMultiMap() noexcept { recursiveDelete(root); }
  void swap(AVLMultiMap & rhs) noexcept {
    std::swap(root, rhs.root);
    std::swap(cmp, rhs.cmp);
  }
  AVLMultiMap & operator=(const AVLMultiMap & rhs) {
    if (this != &rhs) {
      AVLMultiMap temp(rhs);
      this->swap(temp);
    }
    return *this;
  }
  //C++ 11 only
  AVLMultiMap(AVLMultiMap && rhs) noexcept : root(nullptr) { this->swap(rhs); }
  AVLMultiMap & operator=(AVLMultiMap && rhs) noexcept {
    this->swap(rhs);
    return *this;
  }
  //end C++11 only
 private:
  Node * insertHelper(Node * curr, const K & key, const V & val) {
    if (curr == nullptr) {
      return new Node(key, val);
    }
    else if (cmp(key, curr->key)) {
      curr->left = insertHelper(curr->left, key, val);
    }
    else if (cmp(curr->key, key)) {
      curr->right = insertHelper(curr->right, key, val);
    }
    else {
      curr->vals.insert(val);
      return curr;  //no rebalance needed
    }
    return rebalance(curr);
  }
  Node * twoChildDelHelper(Node * curr, Node * replace) noexcept {
    if (curr->left == nullptr) {
      Node * temp = curr->right;
      replace->key = std::move(curr->key);
      replace->vals = std::move(curr->vals);
      delete curr;
      return temp;
    }
    curr->left = twoChildDelHelper(curr->left, replace);
    return rebalance(curr);
  }
  Node * deleteHelper(Node * curr, const K & key, const V & val) noexcept {
    if (curr == nullptr) {
      return nullptr;
    }
    if (cmp(key, curr->key)) {  //key < curr->key
      curr->left = deleteHelper(curr->left, key, val);
    }
    else if (cmp(curr->key, key)) {  //curr->key < key
      curr->right = deleteHelper(curr->right, key, val);
    }
    else {
      //remove val from set.
      curr->vals.erase(val);
      if (!curr->vals.empty()) {
        return curr;  //no change in structure of tree
      }
      //if empty, update structure of tree
      if (curr->left != nullptr && curr->right != nullptr) {
        curr->right = twoChildDelHelper(curr->right, curr);
      }
      else {
        Node * tmp = curr;
        if (curr->left == nullptr) {
          curr = curr->right;
        }
        else {
          assert(curr->right == nullptr);
          curr = curr->left;
        }
        delete tmp;
      }
    }
    return rebalance(curr);
  }
  Node * rebalance(Node * curr) noexcept {
    if (curr == nullptr) {
      return nullptr;
    }
    curr->updateHeight();
    if (curr->tooMuchOnLeft()) {
      if (curr->left->isLeftSideDeeper()) {
        return rightRotate(curr);
      }
      else {
        return leftRightRotate(curr);
      }
    }
    else if (curr->tooMuchOnRight()) {
      if (curr->right->isRightSideDeeper()) {
        return leftRotate(curr);
      }
      else {
        return rightLeftRotate(curr);
      }
    }
    return curr;
  }
  void recursiveDelete(Node * curr) noexcept {
    if (curr == nullptr) {
      return;
    }
    recursiveDelete(curr->left);
    recursiveDelete(curr->right);
    delete curr;
  }
  void preOrderDumpHelper(std::vector<std::pair<std::pair<K, std::set<V> >, int> > & ans,
                          const Node * curr) const {
    if (curr == nullptr) {
      return;
    }
    ans.push_back(std::make_pair(std::make_pair(curr->key, curr->vals), curr->height));
    preOrderDumpHelper(ans, curr->left);
    preOrderDumpHelper(ans, curr->right);
  }

 public:
  std::vector<std::pair<std::pair<K, std::set<V> >, int> > preOrderDump() const {
    std::vector<std::pair<std::pair<K, std::set<V> >, int> > ans;
    preOrderDumpHelper(ans, root);
    return ans;
  }
};
#endif
