#include <printf.h>
unsigned replace_byte(unsigned x, int i, unsigned char b) {
  unsigned char *p = &x;
  p[i] = b;
  return x;
}

int main() {
  unsigned a = replace_byte(0x12345678, 2, 0xAB);
  printf("%x\n", a);
  unsigned b = replace_byte(0x12345678, 0, 0xAB);
  printf("%x\n", b);
}