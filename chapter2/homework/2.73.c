
#include <printf.h>
#include <limits.h>
#include <assert.h>
// Addition that saturates to TMin or TMax.
// 加入饱和到TMin 或 TMax
// 与普通的补码加法不同，饱和加法在出现正溢出时返回 $TMax$，在执行数字信号处理的程序中返回 $TMin$。
int saturating_add(int x, int y) {
  // 正数判断: num & TMin == 0
  // 负数判断: num & TMin == TMin
  int sum = x + y;

  // max = 0 or 1 1表示正溢出
  int max = ((x & INT_MIN) == 0) * ((y & INT_MIN) == 0) * ((sum & INT_MIN) == INT_MIN);

  // min = 0 or 1 1表示负溢出
  int min = ((x & INT_MIN) == INT_MIN) * ((y & INT_MIN) == INT_MIN) * ((sum & INT_MIN) == 0);

  return (max == 1) * INT_MAX + (min == 1) * INT_MIN + (max != 1 && min != 1) * sum;
}

int main() {
  int x = INT_MAX, y = 1;
  printf("%x + %x = %x\n", x, y, saturating_add(x, y));
  assert(saturating_add(x, y) == INT_MAX);

  x = INT_MIN, y = -1;
  printf("%x + %x = %x\n", x, y, saturating_add(x, y));
  assert(saturating_add(x, y) == INT_MIN);

  x = 1, y = 1;
  printf("%x + %x = %x\n", x, y, saturating_add(x, y));
  assert(saturating_add(x, y) == 2);

  x = 0, y = 0;
  printf("%x + %x = %x\n", x, y, saturating_add(x, y));
  assert(saturating_add(x, y) == 0);
}