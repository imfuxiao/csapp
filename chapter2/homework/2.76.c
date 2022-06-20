#include <stddef.h>
#include <stdlib.h>
#include <libc.h>


// malloc() 在堆区分配一块指定大小的内存空间，用来存放数据。这块内存空间在函数执行完成后不会被初始化，它们的值是未知的。
// 返回值: 分配成功返回指向该内存的地址，失败则返回 NULL。
// void *malloc(size_t size)

// memset() 函数用来将指定内存的前n个字节设置为特定的值
// memset() 会将 s 所指的内存区域的前 n 个字节的值都设置为 c, 然后返回指向 s 的指针。
// void *memset(void *s, int c, size_t n);

// 函数calloc为一个数组分配内存, 该数组有nmemb个元素, 每个元素为size字节.
// 内存设置为0
// 如果nmemb或size为0, 则calloc返回NULL
// 编写calloc的实现, 通过调用malloc执行分配, 调用memset将内存设置为0
// 你的代码应该没有任何由算术溢出引起的漏洞, 且无论数据类型size_t用多少位表示, 代码都能正常工作.
void *calloc(size_t nmemb, size_t size) {
  void *p = NULL;

  size_t space = nmemb * size;

  (space == 0) || (p = malloc(space), p != NULL && (p = memset(p, 0, space), p != NULL));

  return p;
}

int main() {
  char *p = calloc(1, 1);
  if (p == NULL) {
    printf("calloc failed");
    return 0;
  }
  p[0] = 0x12;
  p[1] = 0x34;
  p[2] = 0x56;
  p[3] = 0x78;

  int64_t *s= p;
  printf("%x", *s);
  free(p);
}