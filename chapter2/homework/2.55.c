#include <printf.h>
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    printf("addr = %p \t hex = 0x%x\n", p + i, p[i]);
  }
}

void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int));
}

int main() {
  // macos 小端序
  show_int(255);
}