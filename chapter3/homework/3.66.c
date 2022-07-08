#define NR(n) (n * 3)
#define NC(n) (4 * n + 1)

// 3.66

long sum_col(long n , long A[NR(n)][NC(n)], long j) {
  long i;
  long result = 0;
  for (i = 0; i < NR(n); i++) {
    result += A[i][j];
  }
  return result;
}

// 编译这个程序, GCC产生下面的汇编代码:
// long sum_col(long n , long A[NR(n)][NC(n)], long j)
// n in %rdi, A in %rsi, j in %rdx
//  1. sum_col:
//  2.   leaq 1(, %rdi, 4), %r8        # %r8 = 4 * %rdi + 1; %r8 = 4 * n + 1
//  3.   leaq (%rdi, %rdi, 2), %rax    # %rax = 2 * %rdi + %rdi = 3 * %rdi; %rax = 3 * n
//  4.   movq %rax, %rdi               # %rdi = %rax; %rdi = 3 * n
//  5.   test %rax, %rax               # %rax & %rax
//  6.   jle .L4                       # If <= 0; jump L4
//  7.   salq $3, %r8                  # %r8 = %r8 << 3 = %r8 * 8; %r8 = 8 * (4 * n + 1)
//  8.   leaq (%rsi, %rdx, 8), %rcx    # %rcx = %rdx * 8 + %rsi; %rcx = 8 * j + A, 获取A[0][j]的地址
//  9.   movl $0, %eax                 # %rax = 0, 这里将%rax作为result变量的存储
// 10.   movl $0, %edx                 # %rdx = 0, 这里将%rdx作为i的存储
// 11. .L3:
// 12.   addq (%rcx), %rax             # %rax = (%rcx); 获取&A[index]的值
// 13.   addq $1, %rdx                 # %rdx = %rdx + 1; i++
// 14.   addq %r8, %rcx                # %rcx = %rcx + %r8; 计算index,index += %r8, 因为for循环为行加1, 所以index += 8 * NC(n), 所以(第7行) NC(n) = 4*n+1,
// 15.   cmpq %rdi, %rdx               # 比较 %rdx:%rdi; i:NR(n), 说明NR(n) = 3 * n
// 16.   jne .L3                       # If != 0, jump L3
// 17.   rep; ret                      # return
// 18. .L4:
// 19.   movl $0, %eax                 # %rax = 0
// 20.   ret                           # result

// 运用你的逆向工程, 确定NC和NR的定义
// 见 14 ~ 15 注释说明