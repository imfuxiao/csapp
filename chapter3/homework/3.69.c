#define CNT 1

typedef struct {
  long idx;
  long x[4];
} a_struct;
// 3.69

typedef struct {
  int first;
  a_struct a[CNT];
  int last;
} b_struct;

void test(long i, b_struct *bp) {
  int n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}


// void test(long i, b_struct *bp)
// i in %rdi, bp in %rsi
// 1. 0000000000000000 <test>:
// 2.  0: 8b 8e 20 01 00 00  mov 0x120(%rsi), %ecx          # %rcx = %rsi + 288; %rcx = bp->last
// 3.  6: 03 0e              add (%rsi), %ecx               # %rcx += bp->first; 即 n = bp->first + bp->last
// 4.  8: 48 8d 04 bf        lea (%rdi,%rdi,4), %rax        # %rax = 5*%rdi = 5*i
// 5.  c: 48 8d 04 c6        lea (%rsi,%rax,8), %rax        # %rax = 8*%rax + %rsi = bp + 40i
// 6. 10: 48 8b 50 08        mov 0x8(%rax), %rdx            # %rdx = %rax + 8 = bp + 40i + 8
// 7. 14: 48 63 c9           movslq %ecx, %rcx
// 8. 17: 48 89 4c d0 10     mov %rcx, 0x10(%rax,%rdx,8)    # (%rax + %rdx * 8 + 16) = %rcx
// 9. 1c: c3                 retq

// A. CNT的值是多少? 7
// 2~3行: 4 + CNT * sizeof(a_struct) + 内存对齐 = 288
// 4~6行: %rax 保存 bp+40i 的地址, %rdx 保存 ap->idx 的值, 即 bp + 40i + 8
// 说明: a_struct占用字节数为40
// 8 (first 占用 4 个字节 + 字节对齐4个字节) + 40 * CNT = 288
// CNT = 7

// B. a_struct的完整结构
// 4~6行: %rax 保存 bp+40i 的地址, %rdx 保存 ap->idx 的值,
// 8行, (%rax + %rdx*8 + 16) = (bp + 40i + index * 8 + 16) = (bp + 40i + 8 + index * 8 + 8)
// 推论:
// 1. bp + 40i + 8 是 bp->a[i] 的地址, 而地址对应的值正好是a_struct中idx的值, 说明idx在struct前. x在后
// 2. 8 * index: 说明x的类型为8个字节, 在x为long类型
// 3. a_struct结构共40个字节,  x.length * 8 + 8 = 40 => x = 4
// 即: typedef struct {long idx, long x[4]} a_struct;
