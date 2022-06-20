#include <assert.h>
#include <printf.h>
typedef unsigned int float_bits;

float_bits f2u(float f) {
  return *(float_bits *) (&f);
}

float u2f(float_bits f) {
  return *(float *) (&f);
}

int __n = 0x80000000;

// Compute f convert to int
// If conversion causes overflow or f is NaN, return 0x80000000
int float_f2i(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = f >> 23 & 0xff;
  unsigned int frac = f & 0x7fffff;
  unsigned int bias = 0x7f; // 127 0b 0111 1111

  // +∞/-∞/NaN
  if (exp == 0xff) {
    return __n;
  }

  if (exp < bias) {
    return 0;
  }

  // overflow
  // 浮点数的符号位没有权重, 所以不需要这样判断
//  if ((sign == 0 && exp > bias + 30) || (sign == 1 && exp > bias + 31)) {
//    return __n;
//  }
  if (exp > bias + 30) {
    return __n;
  }

  // 0x800000 = 1.000000
  // frac = 0.000000
  // frac | 0x800000 = 1.0 + 0.00000 非规格化
  unsigned int M = frac | 0x800000;
  unsigned int E = exp - bias;

  // M应该为1.xxx小数, 而目前是无符号整数, 相当于给1.xxx小数右移了23位
  // 所以需要给E - 23
  // num = M * 2^(E-23)
  // 因为E-23有可能为负数.
  // 所以当 E >= 23 时: num = M * 2^(E-23) = M << (E-23)
  //     当  E < 23 时: num = M * 2^(E-23) = M >> (23-E)
  unsigned int num;
  if (E >= 23) {
    num = M << (E - 23);
  } else {
    num = M >> (23 - E);
  }
  // 判断符号位
  return sign ? -num : num;
}

int main() {
  printf("%.50f\n", u2f(0x98765432));
  printf("%d\n", (int) u2f(0x98765432));
  printf("%d\n", float_f2i(0x98765432));

  printf("%.50f\n", u2f(0x19802385));
  printf("%d\n", (int) u2f(0x19802385));
  printf("%d\n", float_f2i(0x19802385));

  printf("%.50f\n", u2f(0x78000087));
  printf("%d\n", (int) u2f(0x78000087));
  printf("%d\n", float_f2i(0x78000087));

  printf("%.50f\n", u2f(0x8F088888));
  printf("%d\n", (int) u2f(0x8F088888));
  printf("%d\n", float_f2i(0x8F088888));

  assert(float_f2i(0x98765432) == (int) u2f(0x98765432));
  assert(float_f2i(0x19802385) == (int) u2f(0x19802385));
  assert(float_f2i(0x78000087) == 0x80000000);
  assert(float_f2i(0x8F088888) == (int) u2f(0x8F088888));
  return 0;
}
