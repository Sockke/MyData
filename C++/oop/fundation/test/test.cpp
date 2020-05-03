#include "Queue.h"
using namespace std;

int main() {
  Queue q;
  for (int i = 0; i < 4; ++i) {
    q.push(i);
  }
  cout << "full:" << q.full() << endl;
  while (!q.empty()) {
    cout << q.front() << " " ;
    q.pop();
  }
  cout << endl;
  return 0;
}

#if 0
#include "String.h"

int main() {
  String s1;
  String s2("sock");
  String s3(s2);
  s1 = s3;
  return 0;
}
#endif
