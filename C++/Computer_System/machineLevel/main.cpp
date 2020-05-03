#include <iostream>
using namespace std;

int sum(int a, int b) {
  int x = a + b;
  return x;
}

int main() {
  int a = 10;
  int b = 20;
  int ret = sum(a, b);
  cout << ret << endl; 
  return 0;
}
