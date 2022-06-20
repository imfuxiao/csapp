#include <stdlib.h>
#include <printf.h>
#include <assert.h>
int A(int x, double dx) {
  return (float) x == (float) dx;
}

int B(double dx, double dy, int x, int y) {
  return dx - dy == (double) (x - y);
}

int C(double dx, double dy, double dz) {
  return dx + dy + dz == dx + (dy + dz);
}

int D(double dx, double dy, double dz) {
  return (dx * dy) * dz == dx * (dy * dz);
}

// 0 false
// 当 dx != 0, dz == 0 时
int E(double dx, double dz) {
  return dx / dx == dz / dz;
}

int main() {
  int x = rand();
  int y = rand();
  int z = rand();

  double dx = (double) x;
  double dy = (double) y;
  double dz = (double) z;

  // A. 1 = true. 虽然都转为float, 但由于x与dx都是精确表示32位整数, 所以即使转32位的float有精度丢失的可能, 但转后的值始终相同.
  assert(A(x, dx));

  // B. 0 = false. x-y 有可能溢出, 如当x = 1, y = INT32_MIN时, 溢出. 值为 INT32_MIN. dx - dy 则不会溢出
//  printf("%d\n", (int) (0 - INT32_MIN));
  assert(!B((double) 0, (double) INT32_MIN, 0, INT32_MIN));

  // C. 1 = true dx, dy, dz的都是从32位int转double, 所以dx+dy+dz最多只需要34位表示, 而double为64位. 所以三数相加不会超出精度
  assert(C(dx, dy, dz));

  // D. 0 = false, 三个32位相乘, 会溢出64位.
  assert(D((double) INT32_MIN, (double) INT32_MIN, (double) INT32_MAX));
  assert(!D((double)(int)0x64e73387, (double)(int)0xd31cb264, (double)(int)0xd22f1fcd));

  // E. 0 = false. 当dx!=0, 而dz=0时
  assert(!E(1, 0));
}