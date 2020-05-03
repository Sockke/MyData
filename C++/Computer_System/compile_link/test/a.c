#include <stdio.h>
int a; // 弱符号

void func() {
  a = 1;
}

void show() {
  printf("a = %d\n", a);
}
