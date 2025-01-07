#include <cstdlib>
#include <iostream>

#include "function.h"

class ConstPosFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 1; }  // Always positive
};

class ConstNegFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }  // Always negative
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 4 * arg; }  // Linear function: 4 * x
};

int main() {
  ConstPosFunction constPosFunc;
  ConstNegFunction constNegFunc;
  LinearFunction linearFunc;

  // Run tests
  std::cout << "Running tests..." << std::endl;

  // Test cases
  check(&constPosFunc, 2, 4, 2, "Constant positive function");
  check(&constNegFunc, 6, 6, 6, "Constant negative function");
  check(&constNegFunc, 3, 6, 5, "Constant negative function");
  check(&linearFunc, -2, 5, 0, "Linear function");
  check(&linearFunc, -5, -2, -3, "Linear function");

  std::cout << "All tests passed successfully!" << std::endl;
  return EXIT_SUCCESS;
}
