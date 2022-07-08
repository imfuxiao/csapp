
// 3.67

typedef struct {
  long a[2];
  long *p;
} strA;

typedef struct {
  long u[2];
  long q;
} strB;

strB process(strA s) {
  strB r;
  r.u[0] = s.a[1];
  r.u[1] = s.a[0];
  r.q = *s.p;
  return r;
}

long eval(long x, long y, long z) {
  strA s;
  s.a[0] = x;
  s.a[1] = y;
  s.p = &z;
  strB r = process(s);
  return r.u[0] + r.u[1] + r.q;
}

// GCC 为这两个函数产生下面的代码:
// strB process(strA s)
//  1. process:
//  2.   movq %rdi, %rax          # %rax = %rdi, 对应eval中第8行的值
//  3.   movq 24(%rsp), %rdx      # %rdx = %rsp + 24, 即 &z
//  4.   movq (%rdx), %rdx        # %rdx = &z地址的值, 即z
//  5.   movq 16(%rsp), %rcx      # %rcx = %rsp + 16 = y
//  6.   movq %rcx, (%rdi)        # (%rdi) = %rcx = y
//  7.   movq 8(%rsp), %rcx       # %rcx = %rsp + 8  = x
//  8.   movq %rcx, 8(%rdi)       # (%rdi + 8) = %rcx = x
//  9.   movq %rdx, 16(%rdi)      # (%rdi + 16) = %rdx = z
// 10.   ret

// long eval(long x, long y, long z)
// x in %rdi, y in %rsi, z in %rdx
//  1. eval:
//  2.   subq $104, %rsp         # 开辟栈帧, 共104个字节
//  3.   movq %rdx, 24(%rsp)     # %rsp + 24 = z
//  4.   leaq 24(%rsp), %rax     # %rax = %rsp + 24 的地址; 即&z
//  5.   movq %rdi, (%rsp)       # %rsp = x
//  6.   movq %rsi, 8(%rsp)      # %rsp + 8 = y
//  7.   movq %rax, 16(%rsp)     # %rsp + 16 = &z, 即 %rsp + 24的地址
//  8.   leaq 64(%rsp), %rdi     # %rdi = %rsp + 64的地址
//  9.   call process            # 调用 process
// 10.   movq 72(%rsp), %rax     # %rax = %rsp + 72
// 11.   addq 64(%rsp), %rax     # %rax += %rsp + 64
// 12.   addq 80(%rsp), %rax     # %rax += %rsp + 80
// 13.   addq $104, %rsp
// 14.   ret

// A. 从eval函数的第2行我们可以看到, 它在栈上分配了104个字节. 画出eval的栈帧, 给出它在调用process前存储在栈上的值.
// 调用process前栈帧上的分配
//                    +-------+
//                    |返回地址|
// begin            - |       |
//                 |  |       |
//                 |  |-------| -> %rsp + 64, %rdi同时存储%rsp + 64的地址
//                 |  |       |
//                 |  |-------|
//                 |  |   z   |
// 共104个字节    <-   |-------| -> %rsp + 24
//                 |  |   &z  |
//                 |  |-------| -> %rsp + 16
//                 |  |   y   |
//                 |  |-------| -> %rsp + 8
//                 |  |   x   |
// end              - +-------+ -> %rsp

// B. eval调用process时传递了什么值?
// 由A的栈帧分配图可以得知, %rdi = %rsp+64的地址.

// C. process的代码是如何访问结构参数s的元素的? 由下图得知, 在process执行时, 通过%rsp栈地址+偏移量获取参数s的值
// 注意: 调用process时, call指令会将call process下一条指令的地址作为返回地址压栈. 所以%rsp地址会-8
// 调用process中栈帧上的分配
//                    +-------+
//                    |返回地址|
//                    |-------|
// begin            - |       |
//                 |  |       |
//                 |  |-------|
//                 |  |   z   |
//                 |  |-------| -> %rdi + 16
//                 |  |   x   |
//                 |  |-------| -> %rdi + 8
//                 |  |   y   |
//                 |  |-------| -> %rdi, 对应调用前的%rsp + 64, 注意: 这里的%rsp是调用process前的地址
//                 |  |       |
//                 |  |       |
//                 |  |       |
//                 |  |-------|
//                 |  |   z   |
// 共104个字节    <-   |-------|
//                 |  |   &z  |
//                 |  |-------| -> %rsp + 24
//                 |  |   y   |
//                 |  |-------| -> %rsp + 16
//                 |  |   x   |
// end              - +-------+ -> %rsp + 8
//                    |返回地址| -> call process会导致将call process下一条指令的地址作为返回值压栈
//                    |-------| -> %rsp

// D. process的代码是如何设置结果结构r的字段的? 基于%rdi中存储的%rsp+64的地址, 将r的值保存在栈中.

// E. 完成eval的栈帧图, 给出在从process返回后eval是如何访问结构r的元素的
// 注意: process执行完毕, ret指令会将C图中的返回地址弹栈, 所以%rsp地址会+8
// 调用process中栈帧上的分配
//                    +-------+
//                    |返回地址|
//                    |-------|
// begin            - |       |
//                 |  |       |
//                 |  |-------|
//                 |  |   z   |
//                 |  |-------| -> %rsp + 80
//                 |  |   x   |
//                 |  |-------| -> %rsp + 72
//                 |  |   y   |
//                 |  |-------| -> %rsp + 64
//                 |  |       |
//                 |  |       |
//                 |  |       |
//                 |  |-------|
//                 |  |   z   |
// 共104个字节    <-   |-------| -> %rsp + 24
//                 |  |   &z  |
//                 |  |-------| -> %rsp + 16
//                 |  |   y   |
//                 |  |-------| -> %rsp + 8
//                 |  |   x   |
// end              - +-------+ -> %rsp

// F. 就如何传递作为函数参数的结构, 以及如何作为函数结果的结构值, 你可以看出什么通用的原则?
// 调用者(caller)开辟栈帧空间并将空间地址传递给被调用者(callee)，被调用者(callee)将数据存储在该空间区域并返回该地址