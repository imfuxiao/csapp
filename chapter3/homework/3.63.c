
// 3.63

// long switch_prob(long x, long n)
// x in %rdi, n in %rsi
//  1. 0000000000400590 <switch_prob>:
//  2. 400590: 48 83 ee 3c              sub $0x3c,%rsi                    # n = n - (3*16 + 12) = n - 60, 计算跳转表index
//  3. 400594: 48 83 fe 05              cmp $0x5,%rsi                     # n > 5, 比较 index:5 0~5
//  4. 400598: 77 29                    ja 4005c3 <switch_prob+0x33>      # If >, jump 4005c3, 第 17 行
//  5. 40059a: ff 24 f5 f8 06 40 00     jmpq *0x4006f8(,%rsi,8)           # Goto 4006f8[index], index = 8*%rsi = 8 * (n - 60)
//  6. 4005a1: 48 8d 04 fd 00 00 00     lea 0x0(,%rdi,8),%rax             # %rax = %rdi * 8, result = 8 * x
//  7. 4005a8: 00
//  8. 4005a9: c3                       retq                              # return
//  9. 4005aa: 48 89 f8                 mov %rdi,%rax                     # %rax = %rdi, result = x
// 10. 4005ad: 48 c1 f8 03              sar $0x3,%rax                     # %rax = %rax >> 3, result /= 8
// 11. 4005b1: c3                       retq
// 12. 4005b2: 48 89 f8                 mov %rdi,%rax                     # %rax = %rdi, result = x
// 13. 4005b5: 48 c1 e0 04              shl $0x4,%rax                     # %rax = %rax << 4, result <<= 4
// 14. 4005b9: 48 29 f8                 sub %rdi,%rax                     # result -= x
// 15. 4005bc: 48 89 c7                 mov %rax,%rdi                     # x = result
// 16. 4005bf: 48 0f af ff              imul %rdi,%rdi                    # x = x*x
// 17. 4005c3: 48 8d 47 4b              lea 0x4b(%rdi),%rax               # result = x + (16 * 4 + 11) = x + 75
// 18. 4005c7: c3                       retq                              # return result

//用调试器GDB, 我们可以用命令 x/6gx 0x4006f8 来检查组成跳转表的6个8字节的内存. 如下
// (gdb) x/6gx 0x4006f8
// 0x4006f8: 0x00000000004005a1 0x00000000004005c3
// 0x400708: 0x00000000004005a1 0x00000000004005aa
// 0x400718: 0x00000000004005b2 0x00000000004005bf


// 由上可知跳转表为
// 0x4006f8: 0x00000000
//           0x004005a1  case 0: 6行
//           0x00000000
//           0x004005c3  case 1: 17行
//           0x00000000
//           0x004005a1  case 2: 6行
//           0x00000000
//           0x004005aa  case 3: 9行
//           0x00000000
//           0x004005b2  case 4: 12行
//           0x00000000
//           0x004005bf  case 5: 16行

// 用c代码填写switch语句主体, 使它的行为与机器代码一致.


long switch_prob(long x, long n) {
  long result = x;
  switch (n) {
    case 60:
    case 62:
      result = 8 * x;
      break;
    case 63:
      result = x >> 3;
      break;
    case 64:
      x = (x << 4) - x;
    case 65:
      x = x * x;
    default:
      result = x + 75;
  }
  return result
}