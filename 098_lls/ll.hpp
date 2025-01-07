#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

template<typename T>
class LinkedList {
  friend class Tester;

 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node(const T & item, Node * nextNode = NULL, Node * prevNode = NULL) :
        data(item), next(nextNode), prev(prevNode) {}
  };

  Node * head;
  Node * tail;
  int size;

  // Helper method to clear the list
  void clear() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }

  // Helper method to check invariants - for debugging purposes
  void checkInvariants() const {
    assert((head == NULL && tail == NULL && size == 0) ||
           (head != NULL && tail != NULL && size > 0));
    if (head != NULL) {
      assert(head->prev == NULL);
    }
    if (tail != NULL) {
      assert(tail->next == NULL);
    }
  }

 public:
  // Default constructor
  LinkedList() : head(NULL), tail(NULL), size(0) { checkInvariants(); }

  // Copy constructor
  LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {
    if (rhs.head != NULL) {
      Node * rhsCurr = rhs.head;
      head = new Node(rhsCurr->data);
      Node * lhsCurr = head;
      size++;

      while (rhsCurr->next != NULL) {
        rhsCurr = rhsCurr->next;
        Node * newNode = new Node(rhsCurr->data);
        lhsCurr->next = newNode;
        newNode->prev = lhsCurr;
        lhsCurr = newNode;
        size++;
      }

      tail = lhsCurr;
    }
    checkInvariants();
  }

  // Assignment operator
  LinkedList & operator=(const LinkedList<T> rhs) {
    if (this != &rhs) {
      LinkedList<T> temp(rhs);

      std::swap(head, temp.head);
      std::swap(tail, temp.tail);
      std::swap(size, temp.size);
    }
    return *this;
  }

  // Destructor
  ~LinkedList() { clear(); }

  // Add an item to the front of the list
  void addFront(const T & item) {
    Node * newNode = new Node(item, head, NULL);
    if (head != NULL) {
      head->prev = newNode;
    }
    else {
      tail = newNode;
    }
    head = newNode;
    size++;
    checkInvariants();
  }

  // Add an item to the back of the list
  void addBack(const T & item) {
    Node * newNode = new Node(item, NULL, tail);
    if (tail != NULL) {
      tail->next = newNode;
    }
    else {
      head = newNode;
    }
    tail = newNode;
    size++;
    checkInvariants();
  }

  // Remove an item from the list
  bool remove(const T & item) {
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        if (curr->prev != NULL) {
          curr->prev->next = curr->next;
        }
        else {
          head = curr->next;
        }

        if (curr->next != NULL) {
          curr->next->prev = curr->prev;
        }
        else {
          tail = curr->prev;
        }

        delete curr;
        size--;
        checkInvariants();
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  // Get a reference to the item at a specific index
  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw std::out_of_range("Index out of range");
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  // Get a const reference to the item at a specific index
  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw std::out_of_range("Index out of range");
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  // Find the index of an item in the list
  int find(const T & item) const {
    Node * curr = head;
    int index = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      curr = curr->next;
      index++;
    }
    return -1;  // Item not found
  }

  // Get the size of the list
  int getSize() const { return size; }
};

#endif
