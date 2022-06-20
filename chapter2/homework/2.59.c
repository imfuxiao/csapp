
#include <printf.h>
int main() {
  unsigned int x = 0x89ABCDEF;
  unsigned int y = 0x76543210;
  unsigned int z = (~0xFF & y) | (0xFF & x);
  printf("%x", z);
}