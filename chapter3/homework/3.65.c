#define M 15
// 3.65

void transpose(long A[M][M]) {
  long i, j;
  for (i = 0; i < M; i++) {
    for (j = 0; j < i; j++) {
      long t = A[i][j];
      A[i][j] = A[j][i];
      A[j][i] = t;
    }
  }
}

// 当用优化等级-O1编译时, GCC为这个函数的内循环产生下面的代码:
// 1. .L6:
// 2.    movq (%rdx), %rcx
// 3.    movq (%rax), %rsi
// 4.    movq %rsi, (%rdx)
// 5.    movq %rcx, (%rax)
// 6.    addq $8, %rdx       # %rdx = %rdx + 8, %rdx循环中每次增加8, long类型为8个字节, 说明%rdx保存A[i][j]的指针
// 7.    addq $120, %rax     # %rax = %rax + 120
// 8.    cmpq %rdi, %rax     # 比较 %rax:%rdi
// 9.    jne .L6             # If !=, jump L6
// 我们可以看到GCC把数组索引转换成了指针代码.

// A. 哪个寄存器保存着指向数组元素A[i][j]的指针? %rdx
// 第6行: addq $8, %rdx
// %rdx = %rdx + 8, %rdx循环中每次增加8, long类型为8个字节, 说明%rdx保存A[i][j]的指针

// B. 哪个寄存器保存着指向数组元素A[j][i]的指针? %rax
// 代码2~5行, 交换 %rdx, %rax中的值
// 因为%rdx保存A[i][j], 所以A[j][i]由%rax保存

// C. M的值是多少? 15
// M = 120 / 8 = 15
// A[i][j] 每次步进一个元素
// A[j][i] 每次步进M个元素(指A[M][M]中第二个M), 所以 M = 120 / 8 = 15

