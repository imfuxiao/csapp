// 3.62

// p1 in %rdi, p2 in %rsi, action in %edx
// .L8:                             MODE_E
//   movl $27, %eax       # result = 27
//   ret
// .L3：                            MODE_A
//   movq (%rsi), %rax    # result = *p2
//   movq (%rdi), %rdx    # action = *p1
//   movq %rdx, (%rsi)    # *p2 = action
//   ret
// .L5：                            MODE_B
//   movq (%rdi), %rax    # result = *p1
//   addq (%rsi), %rax    # result += *p2
//   movq %rax, (%rdi)    # *p1 = result
//   ret
// .L6:                             MODE_C
//   movq $59, (%rdi)     # *p1 = 59
//   movq (%rsi), %rax    # result = *p2
//   ret
// .L7:                             MODE_D
//   movq (%rsi), %rax    # result = *p2
//   movq %rax, (%rdi)    # *p1 = result
//   movl $27， %eax      # result = 27
//   ret
// .L9：                            default
//   movl $12, %eax       # result = 12
//   ret

// 填写C代码中缺失的部分, 代码包括落入其他情况中的情况, 试着重建这种情况.
typedef enum { MODE_A, MODE_B, MODE_C, MODE_D, MODE_E } mode_t;

long switch3(long *p1, long *p2, mode_t action) {
  long result = 0;
  switch (action) {
    case MODE_A:
      result = *p2;
      *p2 = *p1;
      break;
    case MODE_B:
      result = *p1 + *p2;
      *p1 = result;
      break;
    case MODE_C:
      *p1 = 59;
      result = *p2;
      break;
    case MODE_D:
      *p1 = *p2;
      result = 27;
      break;
    case MODE_E:
      result = 27;
      break;
    default:
      result = 12;
      break;
  }
  return result;
}