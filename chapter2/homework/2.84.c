
// 填写下列程序的返回值.这个程序测试它的第一个参数是否小于或者等于第二个参数.
// 假定函数f2u返回一个无符号32位数字, 其位表示与它的浮点参数相同.
// 你可以假设两个参数都不是NaN. 两种0, +0与-0被认为是相等的

#include <printf.h>
#include <assert.h>
unsigned f2u(float v) {
  return *(unsigned int *) &v;
}

int float_le(float x, float y) {
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);

  // Get the sign bits
  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;

  return ux == uy
      || sx > sy
      || (sx == 0 && sx == sy && ux < uy)
      || (sx == 1 && sx == sy && ux > uy);
}

int main() {
  float x, y;

  x = 3510593.0f;
  assert(f2u(x) == 0x4A564504);

  x = 2.0f, y = 3.0f;
  assert(float_le(x, y) == (x <= y));

  x = -2.0f, y = 3.0f;
  assert(float_le(x, y) == (x <= y));

  x = 2.0f, y = -3.0f;
  assert(float_le(x, y) == (x <= y));

  x = -2.0f, y = -3.0f;
  assert(float_le(x, y) == (x <= y));

  assert(float_le(+0, -0));
  assert(float_le(0, 3));
  assert(float_le(-4.12, -0));
  assert(float_le(-4, 4));

  assert(float_le(-3.0, 1.0));
  assert(float_le(-4.0, -3.0));
  assert(float_le(1.0, 2.0));

  return 0;
}