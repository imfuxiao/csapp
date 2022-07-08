
// 3.70

union ele {
  struct {
    long *p;
    long y;
  } e1;
  struct {
    long x;
    union ele *next;
  } e2;
};

// 这个声明说明联合中可以嵌套结构.
// 下面的函数(省略了一些表达式)对一个链表进行操作, 链表是以以上联合作为元素的.

void proc(union ele *up) {
  up->e2.x = *((up->e2.next)->e1.p) - (up->e2.next)->e1.y;
}


// A. 下列字段的偏移量是多少?(以字节为单位)
// e1.p:     8
// e1.y:     8
// e1.x:     8
// e1.next:  8

// B. 这个结构总共需要多少字节? e1需要16个字节, e2需要16个字节. 所以 ele共需要16个字节.

// C. 编译器为proc产生以下代码. 补全proc代码
// void proc(union ele *up)
// up in %rdi
// 1. proc:
// 2.   movq 8(%rdi), %rax  # %rax = (%rdi + 8) = (ele->e2).next
// 3.   movq (%rax), %rdx   # %rdx = (%rax) = p
// 4.   movq (%rdx), %rdx   # %rdx = (%rdx) = *p
// 5.   subq 8(%rax), %rdx  # %rdx = %rdx - (%rax - 8) = *p - y
// 6.   movq %rdx, (%rdi)   # (%rdi) = %rdx, e2.x = *p - y
// 8.   ret