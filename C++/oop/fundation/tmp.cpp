#include <iostream>
using namespace std;

int add(int a, int b) {
  return a + b;
}

int main() {
  int (*fun)(int, int) = add;
  (*fun)(1, 2);
  return 0;
}
