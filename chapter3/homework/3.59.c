#include <i386/types.h>

// 3.59

typedef __int128 int128_t;

void store_prod(int128_t *dest, int64_t x, int64_t y) {
  *dest = x * (int128_t) y;
}

// x = 2^64 * x_h + x_l
// y = 2^64 * y_h + y_l
// x * y = (2^64 * x_h + x_l) * (2^64 * y_h + y_l) = 2^128 * x_h * y_h + 2^64 (x_h * y_l + x_l * y_h) + x_l * y_l
// 2^128 会溢出. 所以 x * y = 2^64 (x_h * y_l + x_l * y_h) + x_l * y_l
// 2^64相当于高64位.
// 因为 x_l + y_l 可能存在进位
// 所以 x * y = 2^64 (x_h * y_l + x_l * y_h) + 高64位(x_l * y_l) + 低64位(x_l * y_l)
// 得出:
// 高64位(x * y) = x_h * y_l + x_l * y_h + 高64位(x_l * y_l)
// 低64位(x * y) = 低64位(x_l * y_l)

// 根据以上推导在看汇编代码

// dest in %rdi, x in %rsi, y in %rdx
//
//1.   store_prod:
//2.     movq %rdx, %rax     # %rax = y
//3.     cqto                # 将%rax扩展为8字, 即128位. 其中 %rdx 存放高64位, %rax 存放低64位
//                           # 2~3行: 扩展y, 将y分解为 %rdx = y_h(高64位), %rax = y_l(低64位)
//
//4.     movq %rsi, %rcx     # %rcx = x
//5.     sarq $63, %rcx      # %rcx = %rcx >> 63 = x >> 63, 取x的高8个字节, 即 x_h
//                           # 4~5行: 扩展x, 将x分解为 %rcx = x_h(高64位), %rsi = x_l(低64位)
//
//6.     imulq %rax, %rcx    # %rcx = %rax * %rcx, 即 %rcx = x_h * y_l
//7.     imulq %rsi, %rdx    # %rdx = %rsi * %rdx, 即 %rdx = x_l * y_h
//8.     addq %rdx, %rcx     # %rcx = %rdx * %rcx, 即 %rcx = x_l * y_h  + x_h * y_l
//9.     mulq %rsi           # %rsi * %rax = x_l * y_l, 乘积结果: %rdx 存放高64位, %rax存放低64位
//                           # 即 %rdx = 高64位(x_l * y_l), %rax = 低64位(x_l * y_l)
//
//10.    addq %rcx, %rdx     # %rdx = %rcx + %rdx, 即 %rdx = x_l * y_h  + x_h * y_l + 高64位(x_l * y_l)
//                           # 即: %rdx = 高64位(x * y)
//11.    movq %rax, (%rdi)   # (%rdi) 存放低64位(x * y)
//12.    movq %rdx, 8(%rdi)  # (%rdi + 8) 存放高64位(x * y)
//13.    ret
