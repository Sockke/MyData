#include <iostream>
#include <typeinfo>
#include <cstring>
using namespace std;

// 1. C++为什么支持重载, 而C语言不支持
// C++在编译时期产生的链接符号是由函数名和参数列表中参数的类型共同决定的;
// C在编译时期产生的链接符号只由函数名决定
//
// 2. 什么是函数重载, 函数重载的注意事项
// 1) 函数名相同, 参数列表不同(参数个数不同, 参数类型不同), 构成重载
// 2) 构成重载的前提是, 重载函数在同一作用域中
// 3) const是如何影响函数参数类型的, 比如说const int*与int*, int* const与int*
//
// 3. 重载的意义: 重载是一种静态多态, 在编译时期函数符号确定

// 4. C++如何调用C代码, C如何调用C++代码
// C++调用C代码, 在C++程序中, 将C函数的声明放在extern "C" {} 中
// C调用C++代码, 在C++程序中, 将C++函数的定义放在extern "C" {} 中
// 原理: extern "C"是C++所支持的语法, 其功能就是指明编译时产生函数符号的规则
// 使函数符号按C的方式生成

#if 0
bool compare(int a, int b) {
  return a > b;
}
bool compare(double a, double b) {
  return a > b;
}
bool compare(const char* left, const char* right) {
  return strcmp(left, right) > 0;
}
void func() {
  bool compare(int a, int b);  // 将重载函数声明在另一个函数中
  // 函数的匹配采用就近原则, 不会跳出作用域进行匹配
  // 除非指明被调用函数的作用域, 比如说全局匹配, ::compare(1.1, 2.2), ::compare("hello", "world")
  // 因此构成重载的前提是, 重载函数要处在同一作用域中
  bool ret = compare(1.1, 2.2);
  cout << "ret = " << ret << endl;
  ret = compare("hello", "world");
  cout << "ret = " << ret << endl;
}
#endif

#if 0
// const int* 与 int* const, const int* 与 int* 构成重载
// int* const 与 int* 不构成重载
void func(const int* x) { // 类型名: PKi
  cout << "const int*:" << typeid(x).name() << endl;
}
void func(int* const x) { // 类型名: Pi
  cout << "int* const:" << typeid(x).name() << endl;
}
void func(int* x) { // 类型名: Pi
  cout << "int*:" << typeid(x).name() << endl;
}
#endif

#if 0
extern "C" {
  int sum(int a, int b);
}
extern "C" {
  int sum(int a, int b) {
    return a + b;
  }
}
#endif

// C/C++都可以调用该函数
#if __cplusplus
extern "C" {
#endif
  int sum(int a, int b) {
    return a + b;
  }
#if __cplusplus
}
#endif

//int main() {
//  int a = 10;
//  int b = 20;
//  int ret = sum(a, b);
//  cout << "ret = " << ret << endl;
//  return 0;
//}

