#include <printf.h>
int int_shifts_are_arithmetic() {
  return -1 >> 31 & 1;
}
int main() {
  if (int_shifts_are_arithmetic()) {
    printf("算术右移");
  } else {
    printf("逻辑右移");
  }
}