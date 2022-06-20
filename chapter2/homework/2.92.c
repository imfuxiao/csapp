
#include <assert.h>
// Access bit-level representation floating-point number. 访问位级表示浮点数
typedef unsigned int float_bits;

float u2f(float_bits f) {
  return *(float *) (&f);
}

float_bits f2u(float f) {
  return *(float_bits *) (&f);
}

// Compute -f. if f is NaN, then return f.
float_bits float_negate(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = f >> 23 & 0xff;
  unsigned int frac = f & 0x7fffff;

  // f is NaN
  if (exp == 0xff && frac != 0) {
    return f;
  }

  return ~sign << 31 | exp << 23 | frac;
}

int main() {
  float f1 = 56.0f;
  assert(-f1 == 0 - 56.0);

  float_bits f = 0x4A564504;
  assert(u2f(f) == 3510593.0f);
  assert(f2u(3510593.0f) == f);

  assert(u2f(float_negate(f)) == -3510593.0f);
  assert(float_negate(0x89) == 0x80000089);
  assert(float_negate(0x89999999) == 0x9999999);
  assert(float_negate(0x7F900000) == 0x7F900000);
}