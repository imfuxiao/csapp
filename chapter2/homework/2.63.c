
// 可以通过计算 8*sizeof(int) 来确定数据类型int中的位数w.
// 位移量k的取值范围为 0 ~ w-1

#include <limits.h>
#include <printf.h>
// 函数srl用算数右移(由值xsra给出)来完成逻辑右移
// 后面的其他操作不包括右移或者除法.
unsigned srl(unsigned x, int k) {
  // 执行算术右移
  unsigned xsra = (int) x >> k;
//  printf("xsra = %x\n", xsra);

  // -1 = [1, 1, ..., 1]
  // sizeof(int): int类型字节长度
  // sizeof(int) << 3 = w = 总bit位数
  // (sizeof(int) << 3) - k: 计算需要左移的位数,
  // -1 << ((sizeof(int) << 3) - k) 得到: [1, ..., 1, 0, ..., 0]
  // (k != 0) * -1: 是对当k = 0 的特殊情况处理, k != 0 表达式结果为1或0. 1: true, 0: false,
  // ~: 整体取反是为了获取 [0, ..., 0, 1, ..., 1], 即高k位为0, 其余位为1
  unsigned mark = ~(((k != 0) * -1) << ((sizeof(int) << 3) - k));
//  printf("mark = %x\n", mark);

  return xsra & mark;
}

// 函数sra用逻辑右移(由值xsrl给出)来完成算数右移
// 后面的其他操作不包括右移或者除法.
int sra(int x, int k) {
  // 执行逻辑右移
  int xsrl = (unsigned) x >> k;

//  printf("xsrl = %x\n", xsrl);

  // -1 = [1, 1, ..., 1]
  // sizeof(int): int类型字节长度
  // sizeof(int) << 3 = w = 总bit位数
  // (sizeof(int) << 3) - k: 计算需要左移的位数,
  // -1 << ((sizeof(int) << 3) - k) 得到: [1, ..., 1, 0, ..., 0]
  unsigned mark = -1 << ((sizeof(int) << 3) - k);
//  printf("mark = %x\n", mark);

  return xsrl | mark;
}

int main() {
  int a = -1, k = 2;
  unsigned x = srl(a, k);
  printf("srl(%x, %d) = %x\n", a, k, x);

  a = -1, k = (sizeof(int) << 3) - 1;
  x = srl(a, k);
  printf("srl(%x, %d) = %x\n", a, k, x);

  // bug: 当k=0, 返回值应为自身
  a = -1, k = 0;
  x = srl(a, k);
  printf("srl(%x, %d) = %x\n", a, k, x);

  a = -1, k = 2;
  x = sra(a, k);
  printf("sra(%x, %d) = %x\n", a, k, x);

  a = -1, k = (sizeof(int) << 3) - 1;
  x = sra(a, k);
  printf("sra(%x, %d) = %x\n", a, k, x);

  // bug: 当k=0, 返回值应为自身
  a = -1, k = 0;
  x = sra(a, k);
  printf("sra(%x, %d) = %x\n", a, k, x);
}