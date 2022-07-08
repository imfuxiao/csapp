#include <stdio.h>
// 3.71
// 写一函数good_echo, 它从标准输入读取一行, 再把它写到标准输出.
// 你的实现应该对任意长度的输入行都能工作.
// 可以使用库函数fgets, 但是你必须确保即使当输入行要求比你已为缓冲区分配的更多空间时, 你的函数也能正确的工作.
// 你的代码还应检查错误条件, 在遇到错误条件时返回.
// 参考标准I/O函数定义的文档[45, 61]

#define M 8

void good_echo() {
  char buf[M] = "";
  while (fgets(buf, M, stdin) != NULL) {
    fprintf(stdout, buf);
  }
}

int main() {
  good_echo();
}