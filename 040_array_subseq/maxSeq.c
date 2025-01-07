#include <stdio.h>

int maxSeq(int * array, size_t n) {
  if (array == NULL || n == 0) {
    return 0;
  }
  else if (n == 1) {
    return 1;
  }

  size_t seqMax = 1;
  size_t currentMax = 1;

  for (size_t i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) {
      currentMax++;
      if (currentMax > seqMax) {
        seqMax = currentMax;
      }
    }
    else {
      currentMax = 1;
    }
  }

  return seqMax;
}
