#include <iostream>
using namespace std;

void func(int a, int b) {
  cout << a << endl;
  cout << b << endl;
}

int main() {
  int i = 0;
  func(++i, i++);
  return 0;
}
