#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test_maxSeq(int * array, size_t n, size_t exp_ans) {
  size_t ans = maxSeq(array, n);
  if (ans != exp_ans) {
    printf("Failed: maxSeq Test on array of size %zu returned  %zu, expected %zu\n ",
           n,
           ans,
           exp_ans);

    exit(EXIT_FAILURE);
  }
}

int main(void) {
  // Test case 1: Example test
  int array1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  test_maxSeq(array1, 10, 4);

  // Test case 2:
  int array2[] = {2, 2, 2, 2};
  test_maxSeq(array2, 4, 1);

  // Test case 3:
  int * array3 = NULL;
  test_maxSeq(array3, 0, 0);

  // Test case 4:
  int array4[] = {2, 1, 2, 1, 2};
  test_maxSeq(array4, 5, 2);

  // Test case 5:
  int array5[] = {5, 4, 3, 2, 1};
  test_maxSeq(array5, 5, 1);

  // Test case 6:
  int array6[] = {1, 2, 3, 4, 5};
  test_maxSeq(array6, 5, 5);

  // Test case 7:
  int array7[] = {2, 4, 3, 6, 10, 15, -1, 7, 8};
  test_maxSeq(array7, 9, 4);

  // Test case 8:
  int array8[] = {-10, -9, 2, 3, 2, 3, 4, 5, 6, 7, 7, 8, 9, 11, 12, 13, 14, 14};
  test_maxSeq(array8, 18, 7);

  printf("All tests passed successfully.\n");
  return EXIT_SUCCESS;
}
