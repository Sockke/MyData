#include <stdio.h>
int a;

void func();
void show();
int main() {
  func();
  printf("%d\n", a);
  show();
  return 0;
}
