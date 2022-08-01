  .text
.global pushtest
.type pushtest, @function

pushtest:
  movq %rsp, %rax
  pushq %rsp
  popq %rdx
  subq %rdx, %rax
  ret

.global poptest
.type poptest, @function
poptest:
  movq %rsp, %rdi
  pushq $0xabcd
  popq %rsp
  movq %rsp, %rax
  movq %rdi, %rsp
  ret
