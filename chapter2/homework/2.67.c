#include <printf.h>

// 给你一个任务, 编写一个过程int_size_is_32(), 当在一个int为32位的机器上运行时, 该程序产生1, 其他情况产生0.
// 不允许使用sizeof()运算符.
// 下面是开始时的尝试

// the following code does not run properly on some machines. 已下代码在某些机器上无法运行
int bad_int_size_is_32() {
  // Set most significant bit(msb) of 32-bit machine. 设置32位机器的最高有效位msb
  int set_msb = 1 << 31;
  printf("bad_int_size_is_32, set_msb =  %x\n", set_msb);
  // Shift past msb of 32-bit word.
  int beyond_msb = 1 << 32;
  printf("bad_int_size_is_32, beyond_msb =  %x\n", beyond_msb);

  // set_msb is nonzero when word size >= 32
  // beyond_msb is zero when word size <= 32
  return set_msb && !beyond_msb;
}

int b_int_size_is_32() {
  int set_msb = 1 << 31;
  printf("b_int_size_is_32, set_msb =  %x\n", set_msb);
  int beyond_msb = set_msb << 1;
  printf("b_int_size_is_32, beyond_msb =  %x\n", beyond_msb);
  return set_msb && !beyond_msb;
}

int c_int_size_is_16() {
  int set_msb = 1 << 15 << 1;
  printf("b_int_size_is_32, set_msb =  %x\n", set_msb);
  int beyond_msb = set_msb << 1;
  printf("b_int_size_is_32, beyond_msb =  %x\n", beyond_msb);
  return set_msb && !beyond_msb;
}

int main() {
  printf("%x\n", bad_int_size_is_32());

  // A. 我们的代码在哪个方面没有遵守C语言标准?
  // P41页, 旁注
  // 当移位的位数 k, 大于待移位数的位数 w. 这种行为对于C程序来说是没有保证的.
  // int beyond_msb = 1 << 32;

  // B. 修改代码, 使得它至少为32位的任何机器上都能正确运行
  printf("%x\n", b_int_size_is_32());

  // C. 修改代码, 使得它在int至少为16位任何机器上都能运行
  printf("%x\n", c_int_size_is_16());
}

