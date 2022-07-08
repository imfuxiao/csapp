// 3.58

// long decode2(long x, long y, long z);
// x in %rdi, y in %rsi, z in %rdx, 返回值存放%rax
//decode2:
//  subq  %rdx, %rsi # y -= z
//  imulq %rsi, %rdi # x *= y
//  movq  %rsi, %rax # move y to %rax
//  salq  $63,  %rax # %rax << 63
//  sarq  $63,  %rax # %rax >> 63
//  xorq  %rdi, %rax # x ^ $rax
//  ret

long decode2(long x, long y, long z) {
  y -= z;
  x *= y;
  return x ^ (y << 63 >> 63);
}

int main() {

}