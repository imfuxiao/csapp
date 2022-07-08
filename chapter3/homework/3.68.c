#define A 1
#define B 2

// 3.68

typedef struct {
  int x[A][B]; /* Unknown constants A and B*/
  long y;
} str1;

typedef struct {
  char array[B];
  int t;
  short s[A];
  long u;
} str2;

void setVal(str1 *p, str2 *q) {
  long v1 = q->t;
  long v2 = q->u;
  p->y = v1 + v2;
}

// GCC为setVal产生如下代码:

// void setVal(str1 *p, str2 *q)
// p in %rdi, q in %rsi
// 1. setVal:
// 2.   movslq 8(%rsi), %rax    # %rax = %rsi + 8
// 3.   addq   32(%rsi), %rax   # %rax += %rsi + 32
// 4.   movq   %rax, 184(%rdi)  # %rdi + 184 = %rax
// 5.   ret

// A和B的值是多少? (答案是唯一的.)
// 这个题的难点在于存在内存对齐.
//
// str1字节:
// int x[A][B]:   4 * A * B
// long y:        8
//
// str2字节:
// char array[B]: 1 * B
// int  t:        4
// short s[A]:    2 * A
// long u:        8

// 行2: str2.t = str2 + 1 * B + 字节补齐 = str2 + 8,  B + 字节补齐 = 8, 所以 1 <= B <= 8
// 行3: str2.u = str2 + 8 + 4 + 2 * A + 字节补齐 = str2 + 32, 24 <= 12 + 2A  <= 32, 所以 A in [6, 7, 8, 9, 10]
// 行4: str1.y = str1 + 4*A*B + 字节补齐 = 184, 176 <= 4AB <= 184, 所以 A*B in [44, 45, 46]
// B in [1,2,3,4,5,6,7,8], A in [6,7,8,9,10], A*B in [44, 45, 46]
// 只有数字5, 9, 才符合上面的条件.
// 所以 B = 5, A = 9