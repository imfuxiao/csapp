
#include <assert.h>
// A. 1^{w-k}0^{k}
int A(int k) {
  return -1 << k;
}

// B. 0^{w-k-j} 1^{k} 0^{j}
int B(int k, int j) {
  return (~(-1 << k)) << j;
}

int main() {
  assert(A(4) == 0xfffffff0);
  assert(B(4, 4) == 0x000000f0);
}