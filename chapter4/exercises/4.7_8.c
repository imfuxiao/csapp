#include <stdio.h>

extern int pushtest(long *);
extern long *poptest(long *);

int main() {
  long *addr = NULL;
  int x = pushtest(addr);
  printf("x = %d, addr= %x \n", x, *addr);

  addr = NULL;
  long *ret = poptest(addr);
  printf("ret= %x, addr= %x \n", *ret, *addr);
}