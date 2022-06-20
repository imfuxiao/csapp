
#include <printf.h>
// 当x的任意奇数位等于1时返回1; 否则返回0;
// 假设为32位
int any_odd_one(unsigned x) {
  // 0x5 = 0b0101
  unsigned int mark = 0x55555555;
  return (x & mark) != 0;
}

int main() {
  int x = -1;
  printf("%d\n", any_odd_one(x));
  x = 0;
  printf("%d\n", any_odd_one(x));
  x = 8;
  printf("%d\n", any_odd_one(x));
}
