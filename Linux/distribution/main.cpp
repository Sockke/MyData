#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
using namespace std;

int main() {
  hash<string> hash_func;
  cout << hash_func("A0") << endl;
  cout << hash_func("A1") << endl;
  cout << hash_func("A2") << endl;
  cout << hash_func("A3") << endl;
  return 0;
}
