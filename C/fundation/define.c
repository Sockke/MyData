#include <stdio.h>
/*
  防止头文件被重复包含的方法:预编译或#pragma once
  预编译:
  #ifndef COMMON_H
  #define COMMON_H
  #endif
  pragma:
  #pragma once

  区别:
  1. 处理时期不同, 预编译是在预处理时期, #pragma once是在编译时期进行检查
  2. 检查方式不同, 预编译是检查文件内容, #pragma once是检查物理位置
  3. 性能不同, 预编译由于是检查文件内容, 因此每次都要读取整个文件, 速度慢,
  #pragma once是检查物理位置, 因此不需要读取文件内容, 速度快
  4. #pragma once起初是微软提供的功能, 可移植性不如预编译, 但是现在大部分
  编译器都支持#pragma once, 并且也推荐使用这个

  设置编译器默认对齐数的方法:
  #pragma pack(4)
*/

/*
#define N 100
int main() {
#if N < 0
  printf("N < 0\n");
#elif N == 0
  printf("N = 0\n");
#else
  printf("N > 0\n");
#endif
  return 0;
}
*/
/*
#ifdef N
int main() {
  printf("N = %d\n", N);
  return 0;
}
#else // #ifndef
int main() {
  printf("no define N\n");
  return 0;
}
#endif
*/


#if 0
/*
  宏定义: 可以定义变量和函数
  #define定义, #undef取消

  宏函数, 可以用来定义简单常用的函数, 比如说LOG日志
  ##预算符是用来连接左右符号的
  ##预算符一般是考虑到定义宏函数的时候, 不定参数为空的情况
  如果不定参数为空, 那么左边的","会影响参数列表的格式
  通过##来连接左边的符号, 当不定参为空时, 会带走左边的","
*/
#define SUM(x, y) ((x) + (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define LOG(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOG2(format, ...) printf(format, ##__VA_ARGS__)

int main() {
  int sum = SUM(5, 10);
  printf("sum = %d\n", sum);
  //int max = MAX(5, 10);
  //printf("max = %d\n", max);
  LOG("hehe");
  LOG("%s\n", "hello world");
  return 0;
}
#endif
