#include <iostream>
using namespace std;
const int a = 10;
int b = a;

int main() {
  printf("%p  %p\n", &a, &b);
  return 0;
}
