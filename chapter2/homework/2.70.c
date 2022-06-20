

#include <printf.h>
// Return 1 when x can be represented as an n-bit, 2's-complement number;
// 当x可以用n个bit位的补码表示，返回 1；
// 0 otherwise
// Examples:
// x = 0xFF, n = 8, return 1
// x = 0b0010, n = 3, return 1
// Assume 1 <= n <= w
int fits_bits(int x, int n) {
//  unsigned w = sizeof(int) << 3;
  unsigned mark = (1 *(n != 32) << n) - 1;
  printf("mark = %x\n", mark);
  printf("x && mark = %x\n", x & mark);
  return (x & mark) == x;
}

int main() {
  int x = 0xff, n = 8;
  printf("fits_bits(x = %x, n = %d) = %x\n", x, n, fits_bits(x, n));
  n = 32;
  printf("fits_bits(x = %x, n = %d) = %x\n", x, n, fits_bits(x, n));
  n = 1;
  printf("fits_bits(x = %x, n = %d) = %x\n", x, n, fits_bits(x, n));
}