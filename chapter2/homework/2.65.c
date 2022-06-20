
#include <printf.h>
// 当 x 包含奇数个 1 时返回 1；否则为 0
// 假设 w = 32
// 你的代码最多只能包含12个算数运算符, 位运算符和逻辑运算符
int odd_ones(unsigned x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return x & 1;
}

int main() {
  unsigned x = 0xf1;
  printf("%x", odd_ones(x));
  // 从w=2开始推算
  // 到w=4...
}