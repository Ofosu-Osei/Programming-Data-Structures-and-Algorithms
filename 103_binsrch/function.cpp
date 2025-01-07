#include "function.h"

// Custom log2 function
double log2(double n) {
  return std::log(n) / std::log(2.0);
}

// Helper function to validate binary search with checks
void check(Function<int, int> * f,
                  int low,
                  int high,
                  int expected_ans,
                  const char * mesg) {
  // Compute the maximum allowed invocations
  unsigned max_invocations =
      (low < high) ? static_cast<unsigned>(log2(high - low) + 1) : 1;

  // Wrap the function in CountedIntFn
  CountedIntFn fn(max_invocations, f, mesg);

  // Perform the binary search
  int result = binarySearchForZero(&fn, low, high);

  // Check the answer
  if (result != expected_ans) {
    std::cerr << "In " << mesg << ": c = " << result << " != expected = " << expected_ans
              << std::endl;
    exit(EXIT_FAILURE);
  }
}
