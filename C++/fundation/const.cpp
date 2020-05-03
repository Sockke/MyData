#include <iostream>
using namespace std;

// 1. const在C与C++中的区别: 其编译的方式不同
//
// 在C中: 可以不初始化, 本质上还是变量, 只不过不能作为左值
// 常变量, 所有出现const常变量名字的地方, 在编译时期都被当作普通变量来生成指令
// 在C++中: 必须初始化, 其本质与初始化的方式有关
// 初始化为立即数: 常量, 所有出现const常量名字的地方, 在编译时期都被立即数给直接替换了
// 初始化为变量: 常变量, 所有出现const常变量名字的地方, 在编译时期都被当作普通变量来生成指令
//
// 2. const 修饰的量位于进程地址空间的哪个区域
// 位于栈区

void func() {
  const int a = 10;
  //int arr[a] = {0};
  int* p = (int*)&a;
  *p = 20;
  cout << "a=" << a << "-*(&a)=" << *(&a) << "-*p=" << *p << endl;
}

void func2() {
  int b = 10;
  const int a = b;
  int* p = (int*)&a;
  *p = 20;
  cout << "a=" << a << "-*(&a)=" << *(&a) << "-*p=" << *p << endl;
}

int main() {
  func();
  func2();
  return 0;
}
