
#include <limits.h>
#include <assert.h>
// 该函数要用正确的舍入方式处理 x / (2^k), 并且应该遵循位级整数编码规则.
// Divide by power of 2.
// Assume 0 <= k < w - 1
int divide_power2(int x, int k) {
  int bias = (1 << k) - 1;
  x = x + ((x & INT_MIN) == INT_MIN) * bias;
  return x >> k;
}

int main() {
  int x, k;

  x = 4, k = 2;
  assert(divide_power2(x, k) == 1);

  x = -30, k = 2;
  assert(divide_power2(x, k) == -7);

  x = -30, k = 0;
  assert(divide_power2(x, k) == -30);
}


