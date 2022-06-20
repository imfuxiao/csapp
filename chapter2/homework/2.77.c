
#include <assert.h>
// A. K = 17
// x * 17 = x * (16 + 1) = x * 16 + x = x << 4 + x
int A(int x) {
  return (x << 4) + x;
}

// B. K = -7
// x * -7 = x * (1 - 8) = x - x << 3
int B(int x) {
  return x - (x << 3);
}

// C. K = 60
// x * 60 = x * (64 - 4) = x << 6 - x << 2
int C(int x) {
  return (x << 6) - (x << 2);
}

// D.K = -112
// x * -112 = x * (16 - 128) = x << 4 - x << 7
int D(int x) {
  return (x << 4) - (x << 7);
}

int main() {
  int x = 2;
  assert(A(x) == x * 17);
  assert(B(x) == x * -7);
  assert(C(x) == x * 60);
  assert(D(x) == x * -112);
}