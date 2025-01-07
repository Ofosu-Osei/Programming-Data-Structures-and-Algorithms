#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned int ans = power(x, y);
  if (ans != expected_ans) {
    printf("Input: power(%u, %u)\n", x, y);
    printf("Failed:\n");
    printf("Got: %u, Expected: %u", ans, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  // Test Cases
  run_check(2, 3, 8);  // 2^3 = 8
  run_check(5, 0, 1);  // Any number to the power of 0 should be 1
  run_check(0, 5, 0);  // 0 to any power should be 0
  run_check(1, 0, 1);  // 1 to the power of anything should be 1
  run_check(0, 0, 1);  // 0^0 is usually treated as 1 in programming
  run_check(
      12345, 1, 12345);  // any base raised to the power of 1 returns the base itself
  run_check(2, 31, 2147483648);  // Assuming 32-bit unsigned int

  // If all tests pass
  printf("All test cases passed successfully.\n");
  return EXIT_SUCCESS;
}
