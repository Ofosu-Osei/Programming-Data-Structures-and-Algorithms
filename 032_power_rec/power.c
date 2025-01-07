unsigned power_helper(unsigned x, unsigned y, unsigned ans) {
  // Base case
  if (y == 0) {
    return ans;
  }

  // Tail recursive call
  return power_helper(x, y - 1, ans * x);
}

unsigned power(unsigned x, unsigned y) {
  return power_helper(x, y, 1);
}
