#ifndef OUR_AVL_TREE_HPP
#define OUR_AVL_TREE_HPP
#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <set>
#include <vector>
template<typename K,
         typename V,
         typename CompareK = std::less<K>,
         typename CompareV = std::less<V> >
class AVLMultiMap {
 private:
  class Node {
   public:
    K key;
    std::set<V, CompareV> vals;
    int height;
    Node * left;
    Node * right;
    int getLeftChildHeight() const { return left == NULL ? -1 : left->height; }
    int getRightChildHeight() const { return right == NULL ? -1 : right->height; }
    void updateHeight() {
      height = 1 + std::max(getLeftChildHeight(), getRightChildHeight());
    }
    Node(const K & key_, const V & val_) :
        key(key_), vals(), height(0), left(NULL), right(NULL) {
      vals.insert(val_);
    }
    Node(const K & key_,
         const std::set<V, CompareV> & vals_,
         Node * ileft,
         Node * iright) :
        key(key_), vals(vals_), left(ileft), right(iright) {
      updateHeight();
    }

    int getBalanceDiff() const { return getLeftChildHeight() - getRightChildHeight(); }
    bool tooMuchOnLeft() const { return getBalanceDiff() > 1; }
    bool tooMuchOnRight() const { return getBalanceDiff() < -1; }
    bool isLeftSideDeeper() const { return getBalanceDiff() >= 0; }
    bool isRightSideDeeper() const { return getBalanceDiff() <= 0; }
  };
  Node * root;
  CompareK cmp;

  Node * leftRotate(Node * curr) {
    Node * node = curr->right;
    curr->right = node->left;
    node->left = curr;
    curr->updateHeight();
    node->updateHeight();
    return node;
  }
  Node * rightRotate(Node * curr) {
    Node * node = curr->left;
    curr->left = node->right;
    node->right = curr;
    curr->updateHeight();
    node->updateHeight();
    return node;
  }
  Node * leftRightRotate(Node * curr) {
    curr->left = leftRotate(curr->left);
    return rightRotate(curr);
  }
  Node * rightLeftRotate(Node * curr) {
    curr->right = rightRotate(curr->right);
    return leftRotate(curr);
  }
  Node * copyHelper(const Node * curr) const {
    if (curr == NULL) {
      return NULL;
    }
    return new Node(
        curr->key, curr->vals, copyHelper(curr->left), copyHelper(curr->right));
  }

 public:
  AVLMultiMap() : root(NULL), cmp() {}
  AVLMultiMap(const AVLMultiMap & rhs) : root(copyHelper(rhs.root)), cmp(rhs.cmp) {}
  void add(const K & key, const V & val) { root = insertHelper(root, key, val); }
  void remove(const K & key, const V & val) { root = deleteHelper(root, key, val); }
  ~AVLMultiMap() { recursiveDelete(root); }
  void swap(AVLMultiMap & rhs) {
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

 private:
  Node * insertHelper(Node * curr, const K & key, const V & val) {
    if (curr == NULL) {
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
  Node * twoChildDelHelper(Node * curr, Node * replace) {
    if (curr->left == NULL) {
      Node * temp = curr->right;
      replace->key = curr->key;
      replace->vals = curr->vals;
      delete curr;
      return temp;
    }
    curr->left = twoChildDelHelper(curr->left, replace);
    return rebalance(curr);
  }
  Node * deleteHelper(Node * curr, const K & key, const V & val) {
    if (curr == NULL) {
      return NULL;
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
      if (curr->left != NULL && curr->right != NULL) {
        curr->right = twoChildDelHelper(curr->right, curr);
      }
      else {
        Node * tmp = curr;
        if (curr->left == NULL) {
          curr = curr->right;
        }
        else {
          assert(curr->right == NULL);
          curr = curr->left;
        }
        delete tmp;
      }
    }
    return rebalance(curr);
  }
  Node * rebalance(Node * curr) {
    if (curr == NULL) {
      return NULL;
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
  void recursiveDelete(Node * curr) {
    if (curr == NULL) {
      return;
    }
    recursiveDelete(curr->left);
    recursiveDelete(curr->right);
    delete curr;
  }
  void preOrderDumpHelper(
      std::vector<std::pair<std::pair<K, std::set<V, CompareV> >, int> > & ans,
      const Node * curr) const {
    if (curr == NULL) {
      return;
    }
    ans.push_back(std::make_pair(std::make_pair(curr->key, curr->vals), curr->height));
    preOrderDumpHelper(ans, curr->left);
    preOrderDumpHelper(ans, curr->right);
  }

 public:
  std::vector<std::pair<std::pair<K, std::set<V, CompareV> >, int> > preOrderDump()
      const {
    std::vector<std::pair<std::pair<K, std::set<V, CompareV> >, int> > ans;
    preOrderDumpHelper(ans, root);
    return ans;
  }
};
#endif
