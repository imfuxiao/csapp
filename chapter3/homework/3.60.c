
// 3.60

//long loop(long x, int n)
// x in %rdi, n in %rsi
//  1. loop:
//  3.   movl %esi, %ecx   # %ecx = n
//  4.   movl %1, %edx     # %edx = 1, 即 long mask; mask = 1;
//  5.   movl %0, %eax     # %eax = 0, 即 long result = 0
//  6.   jmp  .L2          # jump L2
//  7. .L3:
//  8.   movq %rdi, %r8    # %r8 = %rdi, %rdi = x, %r8 = x
//  9.   andq %rdx, %r8    # %r8 = %r8 & %rdx, %r8 = x & mask
// 10.   orq  %r8, %rax    # %rax = %rax | %r8, result |= x & mask
// 11.   salq %cl, %rdx    # %rdx = %rdx << %cl, mask <<= n, %cl 是 $ecx 低8位, 2^m=w, w=32(n 为 int, 32位), m = 5, 所以使用%cl
// 12. .L2:
// 13.   testq %rdx, %rdx  # %rdx & %rdx    # mask != 0
// 14.   jne   .L3         # != 0, jump L3
// 15.   rep; ret


// A. 那个寄存器保存着程序值x, n , result和mask?
// x in %rdi, n in %rsi, result in %rax, mask in %rdx

// B. result和mask的初始值是多少?
// result = 0, mask = 1

// C, mask的测试条件是什么?
// mask != 0

// D. mask是如何被修改的?
// 11行 salq %cl, %rdx, 即 mask = mask << n

// E. result是如何被修改的?
// 第8~10行. result |= x & mask

// F. 填写这段C代码缺失的部分
long loop(long x, int n) {
  long result = 0; // 5行
  long mask;
  for (mask = 1; mask != 0; mask = mask << n) {
    result |= x & mask;
  }
  return result;
}
