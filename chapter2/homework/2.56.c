#include <stddef.h>
#include <printf.h>
#include <strings.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer p, size_t len) {
  for (size_t i = 0; i < len; i++) {
    printf("addr: %p \t hex: %x\n", p + i, p[i]);
  }
}

int main() {
  int a = 10;
  printf("----int begin----\n");
  show_bytes((byte_pointer) &a, sizeof(int));
  printf("----int end----\n");

  double b = 100.0;
  printf("----double begin----\n");
  show_bytes((byte_pointer) &b, sizeof(double));
  printf("----double end----\n");

  char *c = "abcdef";
  printf("----char array begin----\n");
  show_bytes((byte_pointer) c, strlen(c));
  printf("----char array end----\n");
}