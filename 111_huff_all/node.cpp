#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    // Check ifLeaf node contains a symbol
    assert(left == NULL && right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
  }
  else {
    // Internal node, both children must exist
    assert(left != NULL && right != NULL);

    // Recurse left with updated BitString
    left->buildMap(b.plusZero(), theMap);

    // Recurse right with updated BitString
    right->buildMap(b.plusOne(), theMap);
  }
}
