#include <iostream>
using namespace std;

// 函数对象(仿函数)
// 什么是函数对象:
// 拥有小括号运算符重载函数的对象叫做函数对象, 或者叫做仿函数
// 函数对象像函数一样使用
//
// 函数对象相比与函数指针有什么优势:
// 1. 函数对象可以自定义记录对函数调用过程的相关信息
// 函数对象是通过类来实现的, 因此可以在类中定义记录函数调用过程的相关信息的成员变量
// 使用起来相对灵活
// 2. 函数对象可以通过内联来提高效率.
// 函数对象的声明和实现都是在类里面的. 在编译时期当调用函数对象时, 可以直接识别成内联函数.
// 但是函数指针不可以, 因为在编译时期不知道你调用了哪个函数, 只有在运行时期才能确定函数地址
// 不能实现内联

#if 0
template <class T>
bool myLess(T a, T b) {
  return a < b;
}
template <class T>
bool myGreater(T a, T b) {
  return a > b;
}

template <class T, class Compare>
bool myCompare(T a, T b, Compare cmp) {
  return cmp(a, b);
}

int main() {
  cout << myCompare(10, 20, myLess<int>) << endl;;
  cout << myCompare(10, 20, myGreater<int>) << endl;
  return 0;
}
#endif

// 在使用一些STL容器时, 如果想改变容器的存放规则, 可以在模板参数中传入函数对象类型
// 在使用一些泛型算法时, 如果想改变算法函数的算法规则, 可以在函数参数中传入函数对象
template <class T>
struct myLess {
  bool operator()(T a, T b) {
    return a < b;
  }
};
template <class T>
struct myGreater {
  bool operator()(T a, T b) {
    return a > b;
  }
};

template <class T, class Compare = myLess<T>>
bool myCompare(T a, T b, Compare cmp = Compare()) {
  return cmp(a, b);
}

int main() {
  cout << myCompare(10, 20) << endl;
  cout << myCompare(10, 20, myGreater<int>()) << endl;
  cout << myCompare<int, myGreater<int>>(10, 20) << endl;;
  return 0;
}
