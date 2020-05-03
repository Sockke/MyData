#include <iostream>
#include <vector>
using namespace std;

int rand5() {
  return rand() % 5;
}
int rand25() {
  return 5 * rand5() + rand5();
}
int rand7() {
  int ret = 0;
  while ((ret = rand25()) >= 21);
  return ret % 7;
}

int main() {
  srand(time(nullptr));
  vector<int> arr;   
  for (int i = 0; i < 10; ++i) {
    arr.push_back(rand7());
  }
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
