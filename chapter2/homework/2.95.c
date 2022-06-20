
#include <assert.h>
typedef unsigned int float_bits;

float_bits f2u(float f) {
  return *(float_bits *) (&f);
}

float u2f(float_bits f) {
  return *(float *) (&f);
}

// Compute 0.5*f. If f is NaN, then return f.
float_bits float_half(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = f >> 23 & 0xff;
  unsigned int frac = f & 0x7fffff;

  // +∞/-∞/NaN return f
  if (exp == 0xff) {
    return f;
  }


  // 右移存在向偶数舍入的问题
  // 当后两位是以下情况时
  // 00 >> 1 = 0 无需进位
  // 01 >> 1 = 0 因需向偶数进位, 无需进位
  // 10 >> 1 = 1 无需进位
  // 11 >> 1 = 0 需进位
  unsigned bias = (frac & 0x3) == 0x3;

  // f = (-1)^s * M * 2^E
  // 0.5 * f = (-1)^s * M * 2^E * 2^-1
  // 特殊情况:
  // 1. 非规格化值, 直接左移, 注意如果向偶数进位问题处理
  // 2. exp==1时, 规格化数需转非规格化数
  if (exp == 0) {
    frac >>= 1;
    frac += bias;
  } else if (exp == 1) { // 规格化数转非规格化数
    unsigned num = f & 0x7fffffff;
    num >>= 1;
    num += bias;

    exp = num >> 23 & 0xff;
    frac = frac & 0x7fffff;

  } else {
    exp -= 1;
  }

  return sign << 31 | exp << 23 | frac;
}

int main() {
  assert(u2f(float_half(f2u(2.0f))) == 2.0f * 0.5f);
  assert(u2f(float_half(f2u(32.22f))) == 32.22f * 0.5f);
}