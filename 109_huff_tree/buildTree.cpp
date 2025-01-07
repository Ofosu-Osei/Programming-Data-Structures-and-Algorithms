#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;

  // Add leaf nodes to priority queue
  for (unsigned i = 0; i < 257; ++i) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  // Build Huffman encoding tree
  while (pq.size() > 1) {
    // Dequeue the two lowest frequency nodes
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();

    // Make a new parent for them
    Node * parent = new Node(left, right);

    // Enqueue back to the priority queue
    pq.push(parent);
  }

  // Return root node if successful or NULL
  return pq.empty() ? NULL : pq.top();
}
