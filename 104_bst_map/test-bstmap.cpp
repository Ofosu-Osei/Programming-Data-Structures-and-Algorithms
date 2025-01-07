#include <cstdlib>
#include <iostream>
#include <string>

#include "bstmap.h"
void testBstMap() {
  BstMap<int, std::string> map;

  // Add elements
  map.add(3, "Three");
  map.add(1, "One");
  map.add(4, "Four");
  map.add(2, "Two");

  // Test lookup
  try {
    std::cout << "Key 1: " << map.lookup(1) << std::endl;
    std::cout << "Key 3: " << map.lookup(3) << std::endl;
    std::cout << "Key 2: " << map.lookup(2) << std::endl;
    std::cout << "Key 4: " << map.lookup(4) << std::endl;
    std::cout << "Key 5: " << map.lookup(5) << std::endl;
  }
  catch (const std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
  }

  // Remove elements
  map.remove(3);
  map.remove(2);

  // Test after removal
  try {
    std::cout << "Key 3: " << map.lookup(3) << std::endl;
  }
  catch (const std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Key 1: " << map.lookup(1) << std::endl;
  std::cout << "Key 4: " << map.lookup(4) << std::endl;
}

int main() {
  testBstMap();
  return EXIT_SUCCESS;
}
