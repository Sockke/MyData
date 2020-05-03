#include <iostream>

using std::cout;
using std::endl;

// 类模板支持偏特化
// 1. 优先匹配完全特化, 其次匹配偏特化, 最后匹配类模板

template <class T>
class Test {
  public:
    Test() {cout << "call Test<T>" << endl;} 
};
// 类的完全特化
template <> 
class Test<const char*> {
  public:
    Test() {cout << "call Test<const char*>" << endl;}
};

// 类的偏特化
template <class T>
class Test<T*> {  // 可以匹配指针类型
  public:
    Test() {cout << "call Test<T*>" << endl;}
};
template <class R, class A1, class A2>
class Test<R(*)(A1, A2)> {  // 可以匹配带2个参数的函数指针类型
  public:
    Test() {cout << "call Test<R(*)(A1, A2)>" << endl;}
};

void show(int id, const char* info) {
  cout << id << ":" << info << endl;
}

int main() {
  Test<int> t1;
  Test<const char*> t2;
  Test<void(int, const char*)> t3;
  Test<void(*)(int, const char*)> t4;
  return 0;
}
