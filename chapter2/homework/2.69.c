#include <printf.h>
// Do rotating left shift. 旋转左移
// Assume 0 <= n < w
// Examples when x = 0x12345678 and w = 32:
// n=4 -> 0x23456781, n = 20 -> 0x67812345
unsigned rotate_left(unsigned x, int n) {
  unsigned mark = (1 << n) - 1;
  unsigned w = sizeof(int) << 3;
  return (x << n) | ((x & mark << (w - n)) >> (w - n));
}

int main() {
  unsigned x = 0x12345678, n = 4;
  printf("rotate_left(x = %x, n = %d) = %x \n", x, n, rotate_left(x, n));
  n = 20;
  printf("rotate_left(x = %x, n = %d) = %x \n", x, n, rotate_left(x, n));
  n = 0;
  printf("rotate_left(x = %x, n = %d) = %x \n", x, n, rotate_left(x, n));
  n = 31;
  printf("rotate_left(x = %x, n = %d) = %x \n", x, n, rotate_left(x, n));
}