
#include <printf.h>
#include <limits.h>
#include <assert.h>
typedef unsigned int float_bits;

float_bits f2u(float f) {
  return *(float_bits *) (&f);
}

float u2f(float_bits f) {
  return *(float *) (&f);
}

// 获取bits模式从第1位为1开始的掩码
unsigned int left_mark(int x) {
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;
  return x;
}

// Compute (float) i
float_bits float_i2f(int i) {
  // 如果i为0 直接转为0
  if (i == 0) {
    return 0;
  }

  unsigned int exp, frac, sign;
  sign = i < 0;

  // 当i为负数时, 转为正数, 统一处理.
  if (i < 0) {
    i = 0 - i;
  }

  unsigned int E = 0;
  unsigned int mark = left_mark(i);
  unsigned int n = (mark >> 1) + 1 * (i != 0);
  while (n != 0) {
    n >>= 1;
    E++;
  }
  if (E != 0) {
    E--;
  }

  exp = E + 127;
  frac = ((i & mark) << (32 - E)) >> 9;

  return sign << 31 | exp << 23 | frac;
}

int main() {
  printf("%.50f\n", u2f(0x40400000));
//  printf("%x\n", float_i2f(3));
  printf("%x\n", float_i2f(-3));
//  printf("%x\n", float_i2f(-3));


  /* Test float_i2f */
  assert(float_i2f(INT_MIN) == 0xCF000000);
  assert(float_i2f(0x00359141) == 0x4A564504);
  assert(float_i2f(0) == 0x0);
  assert(float_i2f(-98765) == 0xC7C0E680);
}