
#include <assert.h>
typedef unsigned int float_bits;

float_bits f2u(float f) {
  return *(float_bits *) (&f);
}

float u2f(float_bits f) {
  return *(float *) (&f);
}

// Compute |f|. If f is NaN, then return f.
float_bits float_absval(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = f >> 23 & 0xff;
  unsigned int frac = f & 0x7fffff;

  // f is NaN
  if (exp == 0xff && frac != 0) {
    return f;
  }

  return 0 << 31 | exp << 23 | frac;
}

int main() {
  float nan = 0x7fc00000;
  assert(u2f(float_absval(f2u(-11.5f))) == 11.5f);
  assert(u2f(float_absval(f2u(-0.0f))) == 0.0f);
  assert(u2f(float_absval(f2u(nan))) == nan);
  assert(u2f(float_absval(f2u(12.15f))) == 12.15f);
}