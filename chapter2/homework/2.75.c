#include <inttypes.h>
#include <printf.h>

// 计算x, y采用补码的形式下, x*y的高w位.
int signed_high_prod(int x, int y) {
  int64_t multi = (int64_t) x * y;
  return multi >> 32;
}

// 通过调用 signed_high_prod 计算无符号数 x*y 的高w位
unsigned unsigned_high_prod(unsigned x, unsigned y) {
  // x * y = (x' + x_{w-1} * 2^w) * (y' + y_{w_1} * 2^w)
  // = x'*y' + (x' * y_{w-1}) * 2^w + (y' * x_{w-1})* 2^w + x_{w-1} * y_{w-1} * 2^2w
  // 因为只需要高w位, 且 x_{w-1} * y_{y-1} >> w = 0
  // (x'*y' + (x' * y_{w-1}) * 2^w + (y' * x_{w-1})* 2^w + x_{w-1} * y_{w-1} * 2^2w) >> w
  // 展开得到
  // (x'*y')>>w + (x' + y_{w-1}) + (y' + x_{w-1})

  // sign_x = x_{w-1}, sign_y = y_{w-1}
  unsigned sign_x = x >> 31, sign_y = y >> 31;

  // x' * y ' >> w = signed_high_prod(x, y)
  // 因为
  return signed_high_prod(x, y) + x * sign_y + y * sign_x;
}

// 提示: 看等式2.18的推导中, 有符号乘积 x*y 与无符号乘积 x'*y' 之间的关系.

int main() {
  unsigned x, y;
  x = 0x12345678, y = 0xFFFFFFFF;
  printf("x = %x, y = %x, x * y -> high_w = %x, %x\n", x, y, unsigned_high_prod(x, y), ((uint64_t)x * y) >> 32);
}