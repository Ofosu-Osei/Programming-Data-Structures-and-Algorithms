#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low + 2 > high) {
    return low;
  }

  while (low + 1 < high) {
    int mid = low + (high - low) / 2;
    int mid_val = f->invoke(mid);

    if (mid_val > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
  }

  return low;
}
