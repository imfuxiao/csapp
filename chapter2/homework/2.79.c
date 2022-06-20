
#include <limits.h>
#include <assert.h>
// 写出函数 mul3div4 的代码, 对于整数参数x, 计算 3 * x / 4
// 但是要遵循位级整数编码规则.
// 你的代码计算 3*x 也会产生溢出
int mul3div4(int x) {
  // 3 * x / 4 => ((2 + 1) * x) / 4 = (x << 1 + x) >> 2
  x = (x << 1) + x;
  int bais = 3; // (1 << 2) - 1
  return (x + ((x & INT_MIN) == INT_MIN) * bais) >> 2;
}

int main() {
  int x = 4;
  assert(mul3div4(x) == 3);


}