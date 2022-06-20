
#include <printf.h>
typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum);
// A. 这段代码错在哪里?
// 字中的编号从0到3, 0在最低有效字节 3在最高有效字节
//  bytenum << 3: 取反了
// Failed attempt at xbyte
//int xbyte(packed_t word, int bytenum) {
//  return (word >> (bytenum << 3)) & 0xFF;
//}

// B: 给出函数的正确实现, 只能使用左右移位和一个减法
int xbyte(packed_t word, int bytenum) {
  return ((word >> ((3 - bytenum) << 3)) << 24) >> 24;
}

int main() {
  packed_t p = 0x12345678;
  int num = 0;
  printf("xbyte(word = %x, num = %d) = %x\n", p, num, xbyte(p, num));
  num = 1;
  printf("xbyte(word = %x, num = %d) = %x\n", p, num, xbyte(p, num));
  num = 2;
  printf("xbyte(word = %x, num = %d) = %x\n", p, num, xbyte(p, num));
  num = 3;
  printf("xbyte(word = %x, num = %d) = %x\n", p, num, xbyte(p, num));
}