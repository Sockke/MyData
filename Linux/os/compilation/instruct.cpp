/*
  一些常见的寄存器: eax, ebx, edx
  eip, esp, ebp
*/

/*
  一些常见的汇编指令: 汇编格式, Linux下为AT&T, Windows下为Intel
  mov $0x10 eax    ---   eax = 0x10
  mov 4(edx) eax   ---   eax = *(int*)(edx+4)
  call 0x123
  push ebp
  pop esp
  ret

  编译成汇编代码:
  gcc -S main.c -o main.s -m32
*/
