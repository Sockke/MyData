#include <iostream>
#include "Queue.h"
using namespace std;

int main() {
  Queue<int> q;
  for (int i = 0; i < 10000; ++i) {
    q.push(i);
    q.pop();
  }
  cout << q.empty() << endl;
  return 0;
}
