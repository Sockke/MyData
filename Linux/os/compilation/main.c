#include <stdio.h>

int main() {
  int a = 10, b = 20, sum = 0;
  __asm__ __volatile__ (
      "movl %0, %%eax;\n\t"
      "addl %1, %%eax;\n\t"
      "addl %2, %%eax;\n\t"
      "movl %%eax, %0;\n\t"
      : "=m"(sum)  // 输出部分, "=m"代表只写, "+"代表读写
      : "r"(a), "r"(b)  // 输入部分, "r"是指自由选择空闲寄存器
      : "eax" // 可能会破坏的寄存器
  );
  printf("sum = %d\n", sum);
  return 0;
}
