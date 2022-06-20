#include <assert.h>
#include <math.h>

// 返回的浮点值与它的无符号参数有相同的位表示
float u2f(unsigned int u) {
  return *((float *) (&u));
}

// 计算2^x的浮点表示.
// 当x太小, 程序返回0.0
// 当x太大, 程序返回+∞
float fpwr2(int x) {
  unsigned int exp, frac;
  unsigned int u;

  // float规格:s = 1, k = 8, n = 23, bias = 127
  // E 规格化最大值 = 0b 11111110 - bias = 2^8-2 - 127 = 127
  // E 规格化最小值 = 0b 00000001 - bias = 1 - 127 = -126
  // E 非规格化值= 1 - bias = -126
  // V = (-1)^s * M * 2^E

  // 2^x 非规格化最小值(min value)形式为: 0b 0 00000000 0{...}1, => 2^-23 * 2^-126 = 2^-149
  // 即: M = 2^-23, E = 1 - bias = -126

  // 2^x 非规格化最大值(min value)形式为: 0b 0 00000000 10{...}0, => 2^-1 * 2^-126 = 2^-127
  // 即: M = 2^-1, E = 1 - bias = -126

  // 2^x 规格化最大值(min value)形式为: 0b 0 11111110 0{...}0, => 2^127
  // 即: M = 1.0, exp = E + bias = 127 + 127 = 254

  if (x < -149) {
    // To small, Return 0.0
    exp = 0;
    frac = 0;
  } else if (x < -126) {
    // Denormalized result  非规格化结果
    exp = 0;
    // frac的形式为 1{22个0}到0{22个0}1之间
    // 即: 1<<22 到 1之间
    // 所以 x=-127时, frac = 1{22个0} = 1 << 22 = 1<<(-127 + 149)
    frac = 1 << (x + 149);
  } else if (x < 128) {
    // Normalized result  规格化结果
    // exp = E + bias
    exp = x + 127;
    frac = 0;
  } else {
    exp = 0xFF;
    frac = 0;
  }

  // pack exp and frac into 32 bits. 将exp与frac压缩到32位bits中
  u = exp << 23 | frac;
  return u2f(u);
}

int main() {
  // p83: float = 3510593.0 => 0x4A564504
  unsigned int u = 0x4A564504;
  assert(u2f(u) == 3510593.0);

  assert(fpwr2(0) == powf(2, 0));
  assert(fpwr2(100) == powf(2, 100));
  assert(fpwr2(-127) == powf(2, -127));
  assert(fpwr2(-100) == powf(2, -100));
  assert(fpwr2(10000) == powf(2, 10000));
  assert(fpwr2(-10000) == powf(2, -10000));
  assert(fpwr2(-149) == powf(2, -149));
  assert(fpwr2(-150)==powf(2, -150));
  assert(fpwr2(-130)==powf(2, -130));
  assert(fpwr2(23)==powf(2, 23));
  assert(fpwr2(130)==powf(2, 130));
}