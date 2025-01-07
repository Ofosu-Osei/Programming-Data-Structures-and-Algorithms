#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int getNthBit(uint32_t number, int bit) {
  if (bit < 0 || bit >= 32) {
    printf("Bit %d is invalid\n", bit);
    exit(EXIT_FAILURE);
  }
  return (number & (1 << bit)) != 0;
}

void numToBits(uint32_t * nums, int nNums, int * bits, int nBits) {
  if (!nums || !bits || nNums < 0 || nBits < 0) {
    exit(EXIT_FAILURE);
  }

  //Check that there is enough space in bits to hold all the bits of "nums"
  if (nNums * 32 != nBits) {
    printf("Invalid call to numToBits! nBits is %d, nNums is %d\n", nBits, nNums);
    exit(EXIT_FAILURE);
  }

  //Put the individual bits of each number into the "bits" array
  for (int i = 0; i < nNums; i++) {
    //Within each number, the most significant bit (bit 31) should
    //come first, and the least significant bit (bit 0) should come last.
    for (int j = 0, k = 31; j < 32; j++, k--) {
      bits[i * 32 + j] = getNthBit(nums[i], k);
    }
  }
}

void doTest(uint32_t * nums, int n) {
  int bits[n * 32];
  numToBits(nums, n, bits, n * 32);
  for (int i = 0; i < n; i++) {
    printf(" %9d (%8X) => ", nums[i], nums[i]);
    for (int j = 0; j < 32; j++) {
      printf("%d", bits[i * 32 + j]);
    }
    printf("\n");
  }
}

int main(void) {
  uint32_t array1[] = {1, 2, 3, 4, 5, 15, 109};
  uint32_t array2[] = {123456789, 987654321};
  int bits[7 * 32 - 1];
  doTest(array1, 7);
  doTest(array2, 2);
  numToBits(array1, 7, bits, 7 * 32 - 1);
  return EXIT_SUCCESS;
}
