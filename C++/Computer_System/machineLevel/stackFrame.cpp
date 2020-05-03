#include <iostream>
using namespace std;

int sum(int a, int b) {
  int tmp = 0;
  tmp = a + b;
  return tmp;
}

int main() {
  int a = 10;
  int b = 20;
  int ret = sum(a, b);
  cout << "ret = " << ret << endl;
  return 0;
}
