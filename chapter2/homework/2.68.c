#include <printf.h>
// Mask with least significant n bits set to 1
// Examples: n = 6 --> 0x3F; n = 17 --> 0x1FFFF;
// Assume 1 <= n <= w
int lower_one_mask(int n) {
  return (1 * (n != sizeof(int) << 3) << n) - 1;
}

// 注意: n = w 的情况
int main() {
  int n = 6;
  printf("lower_one_mask( %d ) = %x\n", n, lower_one_mask(n));
  n = 17;
  printf("lower_one_mask( %d ) = %x\n", n, lower_one_mask(n));
  n = 1;
  printf("lower_one_mask( %d ) = %x\n", n, lower_one_mask(n));
  n = 32;
  printf("lower_one_mask( %d ) = %x\n", n, lower_one_mask(n));
}