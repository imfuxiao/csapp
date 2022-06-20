

#include <limits.h>
#include <printf.h>
// 如果计算 x - y 不溢出, 这个函数就返回 1
// Determine whether arguments can be subtracted without overflow
// 确定是否可以减去参数而不会溢出
int tsub_ok(int x, int y) {

  // 正数判断: num & TMin == 0, true 表示整数
  // 负数判断: num & TMin == TMin, true 表示负数
  // 将y转为-y, x - y = x + (-y), 使用加法判断是否溢出
  y = -y;
  int sum = x + y;
  // 特殊情况: 当 y = INT_MIN时, -y = INT_MIN, 所以不能通过 sum统一判断, 必须单独判断
  // 又因为当y=INT_MIN时, x在int范围内无论等于多少, x - y 都不溢出的.
  return y == INT_MIN || !(
      // x > 0 && y > 0 && x+y < 0
      ((x & INT_MIN) == 0) && ((y & INT_MIN) == 0) && ((sum & INT_MIN) == INT_MIN) ||
          // x < 0 && y < 0 && x+y > 0
          (((x & INT_MIN) == INT_MIN) && ((y & INT_MIN) == INT_MIN) && ((sum & INT_MIN) == 0))
  );
}

int main() {
  int x, y;

  x = -1, y = INT_MAX;
  printf("%x - %x = %x\n", x, y, tsub_ok(x, y));

  x = -2, y = INT_MAX;
  printf("%x - %x = %x\n", x, y, tsub_ok(x, y));

  x = -1, y = INT_MIN;
  printf("%x - %x = %x\n", x, y, tsub_ok(x, y));
}

