#include <printf.h>

int main() {
  int x = 0x1234;
  // A. x的任何位都等于1
  printf("%x\n", ~0x0 | x);
  // B. x的任何位都等于0
  printf("%x\n", 0x0 & x);
  // C. x最低有效字节都等于1
  printf("%x\n", x | 0xff);
  // D. x最高有效字节都等于1
  printf("%x\n", x | (0xff << ((sizeof(int) - 1) << 3)));
}