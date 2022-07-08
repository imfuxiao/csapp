#include <printf.h>

// 3.61

long cread(long *xp) {
  return (xp ? *xp : 0);
}

long cread_alt(long *xp) {
  // 相当于: return !xp ? 0 : *xp;
  long result = 0;
  if (xp != NULL) result = *xp;
  return result;
}

int main() {
  long *xp = NULL;
  printf("%ld\n", cread(xp));
  printf("%ld\n", cread_alt(xp));
}

// 使用gcc编译没有发现 cread 与 cread_alt 的区别
// gcc -S -O0 -o 3.61.s 3.61.c
// -S: 生成汇编
// -O0: 不使用编译优化
