#ifndef __BSET_H__
#define __BSET_H__

#include <iostream>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}
    Node(K key) : key(key), left(NULL), right(NULL) {}
    ~Node() {}
  };

  Node * root;

  Node * add(const K & key, Node * node) {
    if (node == NULL) {
      node = new Node(key);
    }
    else if (node->key < key) {
      node->right = add(key, node->right);
    }
    else if (node->key > key) {
      node->left = add(key, node->left);
    }
    return node;
  }

  void deleteTree(Node * node) {
    if (node != NULL) {
      if (node->left != NULL) {
        deleteTree(node->left);
      }
      if (node->right != NULL) {
        deleteTree(node->right);
      }
      delete node;
    }
  }

  void printTree(Node * node) const {
    if (node->left != NULL) {
      printTree(node->left);
    }
    std::cout << node->key << " ";
    if (node->right != NULL) {
      printTree(node->right);
    }
  }

  Node * remove(Node * node, const K & key) {
    if (node == NULL) {
      return node;
    }
    if (key < node->key) {
      node->left = remove(node->left, key);
    }
    else if (key > node->key) {
      node->right = remove(node->right, key);
    }
    else {
      if (node->left == NULL && node->right == NULL) {
        delete node;
        node = NULL;
      }
      else if (node->left == NULL) {
        Node * temp = node;
        node = node->right;
        delete temp;
      }
      else if (node->right == NULL) {
        Node * temp = node;
        node = node->left;
        delete temp;
      }
      else {
        Node * temp = maxLeft(node->left);
        node->key = temp->key;
        node->left = remove(node->left, temp->key);
      }
    }
    return node;
  }

  Node * copy(Node * node, Node * rhs) {
    if (rhs != NULL) {
      node = new Node;
      node->key = rhs->key;
      node->left = copy(node->left, rhs->left);
      node->right = copy(node->left, rhs->right);
      return node;
    }
    return NULL;
  }

  Node * maxLeft(Node * node) {
    while (node->right != NULL) {
      node = node->right;
    }
    return node;
  }

 public:
  BstSet<K>() : root(NULL) {}

  BstSet<K>(const BstSet<K> & rhs) : root(NULL) { root = copy(root, rhs.root); }

  BstSet<K> & operator=(const BstSet<K> & rhs) {
    if (this != &rhs) {
      BstSet<K> temp(rhs);
      std::swap(root, temp.root);
    }
    return *this;
  }

  virtual void add(const K & key) { root = add(key, root); }

  virtual bool contains(const K & key) const {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return true;
      }
      else if (key > current->key) {
        current = current->right;
      }
      else {
        current = current->left;
      }
    }
    return false;
  }

  virtual void remove(const K & key) { root = remove(root, key); }

  virtual ~BstSet() { deleteTree(root); }

  void printTree() const {
    printTree(root);
    std::cout << "\n";
  }
};

#endif
