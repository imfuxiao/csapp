#include <libc.h>

// Copy integer into buffer if space is available
// WARRING: The following code is buggy
void copy_int(int val, void *buf, int maxbytes) {
  if (maxbytes - sizeof(val) >= 0)
    memcpy(buf, (void *) &val, sizeof(val));
}

// 这段代码使用库函数memcpy. 虽然在这里用这个函数有点刻意, 因为我们只想复制一个int, 但是它说明了一种复制较大数据结构的常见方法.
// 你仔细测试了这段代码后发现, 哪怕maxbytes很小的时候, 它也能把值复制到缓冲区中.
// A. 解释为什么代码中的条件测试总是成功的. 提示: sizeof运算符返回类型为size_t的值.
// size_t为无符号数, maxbytes - sizeof(val) 会隐式转为无符号数. 所以  maxbytes - sizeof(val)  >= 0 永远为true.
// B. 你该如何重写这个测试条件, 使之可以正常工作. if (maxbytes >= sizeof(val))