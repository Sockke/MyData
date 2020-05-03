#include <iostream>
#include <typeinfo>
#include <functional>
using std::cout;
using std::endl;

// 函数模板不支持偏特化, 可以通过完全特化或者函数重载来指定特殊类型的处理
// 模板函数根据实参推演可以实例化最合适的函数模板
// 1. 优先匹配完全特化, 其次匹配合适的重载函数模板

//void show(int id, const char* info) {
//  cout << id << ":" << info << endl;
//}

template <class T>
void func(T a) {
  cout << "call func<T>" << endl;
  cout << typeid(a).name() << endl;
}
// 函数模板的特化
template <>
void func(const char* a) { 
  cout << "call func<const char*>" << endl;
  cout << a << endl;
}

// 函数模板的重载
template <class R, class A1, class A2> // 匹配普通函数
void func(R(*a)(A1, A2)) {
  cout << "call func<R(*)(A1, A2)>" << endl;
  cout << typeid(a).name() << endl;
  cout << typeid(R).name() << endl;
  cout << typeid(A1).name() << endl;
  cout << typeid(A2).name() << endl;
}

template <class R, class T, class A1, class A2> // 可以匹配成员函数
void func(R(T::*a)(A1, A2)) {
  cout << "call func<R(T::*)(A1, A2)>" << endl;
  cout << typeid(a).name() << endl;
  cout << typeid(R).name() << endl;
  cout << typeid(T).name() << endl;
  cout << typeid(A1).name() << endl;
  cout << typeid(A2).name() << endl;
}

template <class T>
void func(T* a) { // 可以匹配指针类型
  cout << "call func<T*>" << endl;
  cout << typeid(a).name() << endl;
}

class Test {
  public:
    void func(int id, const char* info) {
      cout << id << ":" << info << endl;
    }
};

void show() {cout << "hehe" << endl;}
int main() {
  //typedef void(T)();
  //T* FUNC = show;
  //func(FUNC);
  func(show);
  cout << "----------------" << endl;
  //func(&Test::func);
  return 0;
}
