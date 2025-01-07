#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

    Node() : left(NULL), right(NULL) {}
    Node(const K & key, const V & val) : key(key), value(val), left(NULL), right(NULL) {}
    ~Node() {}
  };

  Node * root;

  // Helper function to delete all nodes
  void clear(Node * node) {
    if (node != NULL) {
      if (node->left != NULL) {
        clear(node->left);
      }
      if (node->right != NULL) {
        clear(node->right);
      }
      delete node;
    }
  }

  // Helper function to recursively add a key-value pair
  Node * add(const K & key, const V & value, Node * node) {
    if (node == NULL) {
      node = new Node(key, value);
    }
    else if (key < node->key) {
      node->left = add(key, value, node->left);
    }
    else if (key > node->key) {
      node->right = add(key, value, node->right);
    }
    else {
      // Replacevalue if key already exists
      node->value = value;
    }
    return node;
  }

  // Helper function to find the maximum node in the left subtree
  Node * maxLeft(Node * curr) const {
    while (curr->right != NULL) {
      curr = curr->right;
    }
    return curr;
  }

  // Helper function to remove a key from the tree
  Node * remove(Node * current, const K & key) {
    if (current == NULL) {
      return NULL;
    }
    if (key < current->key) {
      current->left = remove(current->left, key);
    }
    else if (key > current->key) {
      current->right = remove(current->right, key);
    }
    else {
      // Node found
      if (current->left == NULL && current->right == NULL) {
        delete current;
        return NULL;
      }
      else if (current->left == NULL) {
        Node * temp = current->right;
        delete current;
        return temp;
      }
      else if (current->right == NULL) {
        Node * temp = current->left;
        delete current;
        return temp;
      }
      else {
        Node * temp = maxLeft(current->left);
        current->key = temp->key;
        current->value = temp->value;
        current->left = remove(current->left, temp->key);
      }
    }
    return current;
  }

  // Helper function to copy a tree recursively
  Node * copy(Node * rhs) {
    if (rhs == NULL) {
      return NULL;
    }
    Node * newNode = new Node(rhs->key, rhs->value);
    newNode->left = copy(rhs->left);
    newNode->right = copy(rhs->right);
    return newNode;
  }

  // Helper function to print the tree in-order
  void printTree(Node * node) const {
    if (node != NULL) {
      printTree(node->left);
      std::cout << node->key << "::" << node->value << " ";
      printTree(node->right);
    }
  }

 public:
  BstMap() : root(NULL) {}

  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap temp(rhs);
      std::swap(root, temp.root);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) { root = add(key, value, root); }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return curr->value;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    throw std::invalid_argument("Key not found");
  }

  virtual void remove(const K & key) { root = remove(root, key); }

  virtual ~BstMap() { clear(root); }

  void printTree() const {
    printTree(root);
    std::cout << "\n";
  }
};

#endif
