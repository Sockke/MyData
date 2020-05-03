#include <iostream>
#include <mutex>
#include <thread>
using std::cout;
using std::endl;

std::once_flag flag;

void show() {
  cout << "hehe" << endl;
}
void func() {
  std::call_once(flag, show);
}

int main() {
  std::thread t1(func);
  std::thread t2(func);
  std::thread t3(func);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}
