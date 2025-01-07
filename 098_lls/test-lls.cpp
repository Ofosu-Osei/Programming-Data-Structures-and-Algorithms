

#include <cstdlib>
#include <iostream>
#include <string>

#include "ll.hpp"

typedef LinkedList<int> IntList;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(5);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head->data == 5);
    assert(il.tail->data == 5);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);

    il.addFront(15);
    assert(il.head->data == 15);
    assert(il.head->next->data == 5);
    assert(il.tail->data == 5);
    assert(il.head->prev == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
  }
  // many more tester methods

  // Test for addBack method
  void testAddBack() {
    IntList il;
    il.addBack(20);
    assert(il.getSize() == 1);
    assert(il.head->data == 20);
    assert(il.tail->data == 20);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);

    il.addBack(25);
    assert(il.getSize() == 2);
    assert(il.head->data == 20);
    assert(il.tail->data == 25);
    assert(il.head->next->data == 25);
    assert(il.tail->prev->data == 20);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
  }

  // Testing for operator[] method
  void testOperatorIndex() {
    IntList il;
    il.addBack(60);
    il.addBack(70);
    il[1] = 75;
    assert(il[1] == 75);
    assert(il.head->data == 60);
    assert(il.head->next->data == 75);
    assert(il.tail->data == 75);
    assert(il.tail->prev->data == 60);
  }

  // Testing for find method
  void testFind() {
    IntList il;
    il.addBack(150);
    il.addBack(200);
    il.addBack(250);
    assert(il.find(200) == 1);
    assert(il.find(300) == -1);  // Element not in list
  }

  // Testing for getSize method
  void testGetSize() {
    IntList il;
    assert(il.getSize() == 0);
    il.addBack(110);
    assert(il.getSize() == 1);
    il.addFront(120);
    assert(il.getSize() == 2);
  }

  void testRuleOfThree() {
    // Test Copy Constructor
    IntList il1;
    il1.addBack(10);
    il1.addBack(20);
    il1.addBack(30);

    IntList il2(il1);
    assert(il2.getSize() == 3);
    assert(il2[0] == 10);
    assert(il2[1] == 20);
    assert(il2[2] == 30);

    // Modify il1 and check that il2 is unchanged
    il1.addBack(40);
    assert(il1.getSize() == 4);
    assert(il2.getSize() == 3);

    // Test Assignment Operator
    IntList il3;
    il3.addBack(5);
    il3 = il1;  // Assignment operator
    assert(il3.getSize() == 4);
    assert(il3[0] == 10);
    assert(il3[1] == 20);
    assert(il3[2] == 30);
    assert(il3[3] == 40);
  }

  void testRemoveFromBeginning() {
    IntList a;
    a.addBack(1);
    a.addBack(2);
    a.addBack(3);

    // Remove head node
    assert(a.remove(1) == true);
    assert(a.head->data == 2);
    assert(a.getSize() == 2);
    assert(a.head->prev == NULL);

    // Remove new head node
    assert(a.remove(2) == true);
    assert(a.head->data == 3);
    assert(a.getSize() == 1);
    assert(a.head->prev == NULL);
    assert(a.head == a.tail);  // Only one element left

    // Remove last element in list
    assert(a.remove(3) == true);
    assert(a.head == NULL);
    assert(a.tail == NULL);
    assert(a.getSize() == 0);
  }

  void testRemoveFromMiddle() {
    IntList a;
    a.addBack(1);
    a.addBack(2);
    a.addBack(3);
    a.addBack(4);

    // Remove from the middle
    assert(a.remove(2) == true);
    assert(a.getSize() == 3);
    assert(a.head->next->data == 3);
    assert(a.head->next->prev == a.head);

    // Remove another middle element
    assert(a.remove(3) == true);
    assert(a.getSize() == 2);
    assert(a.head->next == a.tail);
    assert(a.tail->data == 4);
    assert(a.tail->prev == a.head);
  }

  void testRemoveFromEnd() {
    IntList a;
    a.addBack(1);
    a.addBack(2);
    a.addBack(3);

    // Remove tail node
    assert(a.remove(3) == true);
    assert(a.tail->data == 2);
    assert(a.getSize() == 2);
    assert(a.tail->next == NULL);

    // Remove new tail node
    assert(a.remove(2) == true);
    assert(a.tail->data == 1);
    assert(a.getSize() == 1);
    assert(a.tail->next == NULL);
    assert(a.head == a.tail);

    // Remove last remaining element
    assert(a.remove(1) == true);
    assert(a.head == NULL);
    assert(a.tail == NULL);
    assert(a.getSize() == 0);
  }

  void testRemoveSingleElement() {
    IntList a;
    a.addBack(1);

    // Remove only element in list
    assert(a.remove(1) == true);
    assert(a.head == NULL);
    assert(a.tail == NULL);
    assert(a.getSize() == 0);
  }

  void testRemoveNonExistentElement() {
    IntList a;
    a.addBack(1);
    a.addBack(2);
    a.addBack(3);

    // Try removing an element not in the list
    assert(a.remove(4) == false);
    assert(a.getSize() == 3);  // Size should not change
    assert(a.head->data == 1);
    assert(a.head->next->data == 2);
    assert(a.tail->data == 3);
    assert(a.head->next->next == a.tail);
  }

  void testRemovals() {
    testRemoveFromBeginning();
    testRemoveFromMiddle();
    testRemoveFromEnd();
    testRemoveSingleElement();
    testRemoveNonExistentElement();
  }

  void runAllTestCases() {
    testDefCtor();
    testAddFront();
    testAddBack();
    testOperatorIndex();
    testFind();
    testGetSize();
    testRuleOfThree();
    testRemovals();
  }
};

// Main function for testing
int main() {
  Tester t;
  t.runAllTestCases();
  std::cout << "All IntList test cases passed!" << std::endl;
  return EXIT_SUCCESS;
}
