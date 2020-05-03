#include <stdio.h>
/*
  const与define:
  1. 处理时期不同, define在预处理时期进行宏替换
  const在编译时期确定其值
  2. 性能不同, define修饰的宏常量本质上是立即数, 
  程序中有多少个宏常量就分配多少块内存
  const修饰的常变量本质上是变量, 在全局中定义的const变量是存放在ro-data段的(只读数据段),
  只分配一次内存, 程序中其他变量引用的是const变量的地址(从汇编中可以看出)
  因此const的优势要大一些

  const在C和C++中的区别?
*/

int main() {
  return 0;
}
