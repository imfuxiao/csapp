
#include <assert.h>
typedef unsigned int float_bits;

float_bits f2u(float f) {
  return *(float_bits *) (&f);
}

float u2f(float_bits f) {
  return *(float *) (&f);
}

// Compute 2*f. If f is NaN, then return f.
// 因为 f = (-1)^s * M * 2^E
// 所以 2*f = (-1)^s * M * 2^(E+1)
// 特殊情况:
// 1. 非规格话数据 直接移动frac
// 2. 规格化数据 需要考虑exp = 0xff 的情况
float_bits float_twice(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = f >> 23 & 0xff;
  unsigned int frac = f & 0x7fffff;

  // f is NaN
  if (exp == 0xff && frac != 0) {
    return f;
  }

  if (exp == 0) {
    frac = frac << 1;
  } else {
    exp += 1;
  }

  // ∞
  if (exp == 0xff) {
    frac = 0;
  }

  return sign << 31 | exp << 23 | frac;
}

int main() {
  assert(u2f(float_twice(f2u(2.0f))) == 2.0f * 2);
  assert(u2f(float_twice(f2u(0.125f))) == 0.125f * 2);
}