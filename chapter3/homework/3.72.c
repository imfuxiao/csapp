
// 3.72


// C代码
#include <alloca.h>
long aframe(long n, long idx, long *q) {
  long i;
  long **p = alloca(n * sizeof(long *));
  p[0] = &i;
  for (i = 1; i < n; ++i)
    p[i] = q;
  return *p[idx];
}

// 部分汇编代码
// long aframe(long n, long idx, long *q)
// n in %rdi, idx in %rsi, q in %rdx
// 1. aframe:
// 2.   pushq %rbp
// 3.   movq %rsp, %rbp
// 4.   subq $16, %rsp            # Allocate space for i (%rsp = s1)
// 5.   leaq 30(, %rdi, 8), %rax  # %rax = 8* %rdi + 30, 30 = 0b1_1110, 8 * %rdi = 8的倍数, 即 0b1_0000 的倍数
// 6.   andq $-16, %rax           # %rax = -16 & %rax, -16 = 0xFFFFFFFFFFFFFFF0, 等于将%rax后4为至为0, 则%rax为8的整数倍
// 7.   subq %rax, %rsp           # Allocate space for array p (%rsp = s2)
// 8.   leaq 15(%rsp), %r8
// 9.   andq $-16, %r8             # Set %r8 to &p[0]

// A. 用数学语言解释s2的逻辑.
// 第5行, %rax = 8*n + 30
// 第6行, %rax = (8*n + 30) & -16 = (8*n + 0b1_1110) & 0xFF_FF_FF_FF_FF_FF_FF_F0, 向下舍入16的倍数
// (8*n + 30) & 0xFF_FF_FF_FF_FF_FF_FF_F0
// = (8*n + 30) - (8*n + 30) mod 16
// 当n为偶数时: (8*n + 30) mod 16 = (16 * n / 2 + 30) mod 16 = 30 mod 16 = 14
// 当n为奇数时: (8*n + 30) mod 16 = (16 * ( (n + 1)/2 - 1/2 ) + 30) mod 16 = (16 * (n + 1) / 2  - 8 + 30) mod 16 = 22 mod 16 = 6
// 所以 (8*n + 30) - (8*n + 30) mod 16
// 当n为偶数时, = (8*n + 30) - 14 = 8*n + 16
// 当n为奇数时, = (8*n + 30) - 6 = 8*n + 24

// B. 用数学语言解释p的逻辑.
// 第8行, %r8 = %rsp + 15, %r8加偏置值15(15 = 2^4 - 1)
// 第9行, %r8 = %r8 & -16 = (%rsp + 0xF) & 0xFF_FF_FF_FF_FF_FF_FF_F0, 舍到后4位
// 综上: p值为向上舍入16的倍数.

// C. 确定使 e1 的值最小和最大的 n 和 s1 的值
// e1最大值 24, n为奇数
// e1最小值 1, n为偶数

// D. 这段代码为s2和p的值保证了怎样的对齐属性?
// s2 将 8*n 大小 加 偏移量 16 的值 对齐
// p 以 16 的倍数对齐