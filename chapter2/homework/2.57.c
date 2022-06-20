#include <stddef.h>
#include <printf.h>
typedef unsigned char *bytes_pointer;

void show_bytes(bytes_pointer p, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    printf("pointer_address = %p \t hex = %x\n", p + i, p[i]);
  }
}

void show_short(short x) {
  printf("----show short begin----\n");
  show_bytes((bytes_pointer) &x, sizeof(short));
  printf("----show short end----\n");
}

void show_long(long x) {
  printf("----show long begin----\n");
  show_bytes((bytes_pointer) &x, sizeof(long));
  printf("----show long end----\n");
}

void show_double(double x) {
  printf("----show double begin----\n");
  show_bytes((bytes_pointer) &x, sizeof(double));
  printf("----show double end----\n");
}

int main() {
  // short: 2个字节 所以 0x123456789 截取高位, 保留低16位
  // 因为是小端序, 所以先输出89, 在输出67
  short a = 0x123456789;
  show_short(a);

  // long: 8个字节 而0x1234567890 只有5个字节. 所以有3个字节使用0占位
  long b = 0x1234567890;
  show_long(b);

  // double: 8个字节
  double d = 2.123456789;
  show_double(d);
}