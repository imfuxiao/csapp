
#include <printf.h>
// 检测是否小端序
// 1: 小端序
// 0: 大端序
int is_little_endian() {
  unsigned short s = 0xff00;
  unsigned char *p = (unsigned char *) &s;
  return p[0] == 0x00;
}

int main() {
  if (is_little_endian()) {
    printf("is little endian");
  } else {
    printf("is big endian");
  }
}