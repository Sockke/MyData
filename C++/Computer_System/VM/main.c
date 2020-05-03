// nm a.out  查看符号表中所有符号的逻辑地址(线性地址/虚拟地址)
// cat /proc/4702/maps  查看进程虚拟地址空间的使用状况
// 内核需要记住线性区间的使用情况

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g = 10;

int add(int a, int b) {
  return a + b;
}

int main() {
  int a = 1;
  int b = 2;
  printf("&a = %p\n", &a);
  printf("&b = %p\n", &b);
  printf("&g = %p\n", &g);
  printf("add = %p\n", add);
  printf("main = %p\n", main);
  sleep(100);
  return 0;
}
