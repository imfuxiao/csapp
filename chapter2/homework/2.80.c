
#include <limits.h>
#include <assert.h>
// 写出函数 threefourths 的代码.
// 对于整数参数x, 计算 (3/4) * x 的值. 向零舍入. 它不会溢出. 函数应该遵循位级整数编码规则.
int threeforths(int x) {
  int bias = 3; // 2 ^ k - 1 = 2^2 - 1 = 3
  int sign = (x & INT_MIN) == INT_MIN;

  // x = b + f.
  int b = x & (~0x3), f = x & 0x3;

  // x * (3/4) = (b + f) * (3/4)
  // = b * (1/4) * (2 + 1) + f * (2 + 1) * (1/4)
  // b: 不关心小数部分, 所以不考虑偏置数
  int div4 = b >> 2;
  int div4mul3 = (div4 << 1) + div4;

  // f * (2 + 1) * (1/4) = (f << 1 + f) >> 2
  // 小数部分, 需要考虑偏置值
  int mul3div4 = (((f << 1) + f) + sign * bias) >> 2;

  return div4mul3 + mul3div4;
}

int main() {
  assert(threeforths(8) == 6);
  assert(threeforths(9) == 6);
  assert(threeforths(10) == 7);
  assert(threeforths(11) == 8);
  assert(threeforths(12) == 9);

  assert(threeforths(-8) == -6);
  assert(threeforths(-9) == -6);
  assert(threeforths(-10) == -7);
  assert(threeforths(-11) == -8);
  assert(threeforths(-12) == -9);
}