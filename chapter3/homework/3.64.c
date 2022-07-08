
// 3.64
long A[R][S][T]

long store_ele(long i, long j, long k, long *dest) {
  *dest = A[i][j][k];
  return sizeof(A);
}


// 公式3.1
// 声明数组: T D[R][C]
// &D[i][j] = x_d + L * ( C * i + j)
// L: 数据类型T以字节为单位的大小


// A. 三维公式
// 声明数组: T A[R][S][D]
// &A[i][j][k] = x_d + L * (S * D * i + D * j + k)
// L: 数据类型T以字节为单位的大小

// B. 推导 R, S, T 的值
// long store_ele(long i, long j, long k, long *dest)
//  i in %rdi, j in %rsi, k in %rdx, dest in %rcx
//  1. store_ele:
//  2.   leaq (%rsi, %rsi, 2), %rax  # %rax = %rsi * 3, %rax = 3 * j
//  3.   leaq (%rsi, %rax, 4), %rax  # %rax = 4 * %rax + %rsi, %rax = 12 * j + j = 13 * j
//  4.   movq %rdi, %rsi             # %rsi = %rdi = i,
//  5.   salq $6, %rsi               # %rsi = %rsi << 6, %rsi = i * 64
//  6.   addq %rsi, %rdi             # %rdi = %rdi + %rsi, %rdi = i + i * 64 = 65 * i
//  7.   addq %rax, %rdi             # %rdi = %rdi + %rax, %rdi = 65 * i + 13 * j
//  8.   addq %rdi, %rdx             # %rdx = %rdx+ %rdi, %rdx = k + 65 * i + 13 * j
//  9.   movq A(, %rdx, 8), %rax     # %rax = %rdx * 8 + A, %rax = 8 * (k + 65 * i + 13 * j) + A
// 10.   movq %rax, (%rcx)           # (%rcx) = %rax
// 11.   movl $3640, %eax            # %rax = 3640
// 12.   ret                         # return

// 由三维公式得出: S * T = 65, T = 13, S = 5,  R = 3640 / 8 / S / T = 7
