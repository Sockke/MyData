#include <iostream>
using namespace std;

// set_new_handler
// 当内存分配失败时所调用的一个函数
// 这个函数可能会做3种事情:
// 1. 抛出bad_alloc异常
// 2. 调用terminate终止程序
// 3. 获取更多的内存
// 该函数默认是set_new_handler(nullptr), 抛出bad_alloc异常
// 当用户安装自己的new_handler时, 内存分配失败后会调用自己的new_handler,
// 如果再次失败, 则循环调用自己的new_handler, 直到分配失败多次后, 系统会
// 自动调用set_new_handler(nullptr)来抛出bad_alloc异常

void my_new_handler() {
  cout << "out of the range" << endl;
  set_new_handler(nullptr);
}

int main() {
  set_new_handler(my_new_handler);
  char* p = new char[1024 * 1024 * 1024 * 2];
  printf("p = %p\n", p);
  return 0;
}
