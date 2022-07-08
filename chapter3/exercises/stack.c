#include <printf.h>
#include <string.h>

int main() {
  long local;
  printf("local at %p\n", &local);
  char *s = "abcdefg";
  printf("str len: %d\n", strlen(s));
}