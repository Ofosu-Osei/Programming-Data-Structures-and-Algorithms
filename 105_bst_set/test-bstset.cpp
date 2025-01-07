#include <cstdlib>
#include <iostream>
#include <string>

#include "bstset.h"

void testBstSetWithString() {
  BstSet<std::string> set;
  set.add("apple");
  set.add("banana");
  set.add("cherry");
  set.add("date");

  // Test contains
  std::cout << (set.contains("banana") ? "Found banana" : "Did not find banana")
            << std::endl;
  std::cout << (set.contains("fig") ? "Found fig" : "Did not find fig") << std::endl;

  // Test remove
  set.remove("banana");
  std::cout << (set.contains("banana") ? "Found banana after removal"
                                       : "Did not find banana after removal")
            << std::endl;

  // Print tree
  set.printTree();
}

void testBstSet() {
  BstSet<int> set;

  // Add elements to the set
  set.add(10);
  set.add(5);
  set.add(15);
  set.add(3);
  set.add(7);
  set.add(20);
  set.add(5);

  BstSet<int> set2;
  set2.add(10);
  set2.add(15);

  // Assign set1 to set2
  set2 = set;

  // Print set2
  std::cout << "Set2 after assignment, elements:\n";
  set.printTree();

  // Check for elements
  std::cout << "Contains 10: " << (set2.contains(10) ? "Yes" : "No") << std::endl;
  std::cout << "Contains 7: " << (set2.contains(7) ? "Yes" : "No") << std::endl;
  std::cout << "Contains 20: " << (set2.contains(20) ? "Yes" : "No") << std::endl;
  std::cout << "Contains 99: " << (set2.contains(99) ? "Yes" : "No") << std::endl;

  // Remove elements
  set.remove(10);
  set2.remove(7);
  set2.remove(15);

  // Print the tree after removals
  std::cout << "Tree after removing elements: ";
  set2.printTree();

  // Check for elements after removal
  std::cout << "Contains 10: " << (set2.contains(10) ? "Yes" : "No") << std::endl;
  std::cout << "Contains 7: " << (set2.contains(7) ? "Yes" : "No") << std::endl;
  std::cout << "Contains 15: " << (set2.contains(15) ? "Yes" : "No") << std::endl;

  // Add more elements and print again
  set2.add(25);
  set2.add(1);
  std::cout << "Tree after adding more elements: ";
  set2.printTree();
}

int main() {
  testBstSet();
  testBstSetWithString();
  return EXIT_SUCCESS;
}
