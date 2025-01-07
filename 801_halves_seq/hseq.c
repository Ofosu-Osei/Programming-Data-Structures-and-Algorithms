#include <stdio.h>
#include <stdlib.h>

//Helper function for hseq
unsigned countVSeq(unsigned n, double product, unsigned position) {
  //Base case: when we reach the end of sequence
  if (position == n) {
    if (product < 1) {
      return 1;
    }
    return 0;
  }

  //Tesst for invalid seq before last position
  if (product < 1) {
    return 0;
  }

  //Set count for the next element (3/2 or 1/2)
  unsigned count = 0;

  //Use 3/2 for current position
  count += countVSeq(n, product * 1.5, position + 1);

  //Use 1/2 for current position
  count += countVSeq(n, product * 0.5, position + 1);

  return count;
}

unsigned hseq(unsigned n) {
  //start with product 1 and pos 0
  return countVSeq(n, 1.0, 0);
}

// you should not need to modify main
int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage ./hseq start end\n");
    return EXIT_FAILURE;
  }
  unsigned start = atoi(argv[1]);
  unsigned end = atoi(argv[2]);
  for (unsigned i = start; i <= end; i++) {
    printf("%u: %u\n", i, hseq(i));
  }
  return EXIT_SUCCESS;
}
