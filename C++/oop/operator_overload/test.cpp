#include "complex.h"
using namespace std;

// 常用的运算符重载:
// 1. 加法运算符:
// Complex operator+(const Complex& com);
// 对象是作为右值来调用operator+的, 不改变参与相加的对象, 相加后产生一个新的临时对象返回
// 2. 前置++
// Complex& operator++();
// 单目运算符, 参数列表为空代表前置运算符, 对象本身加1, 返回该对象的引用
// 3. 后置++
// Complex operator++(int);
// 单目运算符, 参数列表为int代表后置运算符, 先返回对象的一个临时变量, 然后自身再加1
// 4. 输出运算符:
// friend std::ostream& operator<<(std::ostream& ost, const Complex& com);
// 为了使<<放在对象的前面, 必须设置operator<<的第一个参数为std::ostream, 因此可以通过友元函数实现
// 为了支持连续输出, 返回对象的引用
//
// Complex operator+(const Complex& com);
// 1. com1 + com2: com1.operator+(com2), 符合operator+对象和参数的需求
// 2. com1 + 10: com1.operator+(10), 将10传入之后开始在Complex类中寻找单参的构造函数, 如果有则成功
// 3. 10 + com1: 10.operator+(com1), 10这个对象没有重载operator+(const Complex& com), 所以失败
// 解决: 挣脱对象的束缚
// friend Complex operator+(const Complex& com1, const Complex& com2);
// 使用友元函数设置为全局的运算符重载, 使操作数都作为参数
//
// 运算符的查找流程: 先从类中查找成员运算符重载函数, 最后在全局查找全局运算符重载函数
//
int main() {
  Complex c1(10, 10);
  Complex c2(20, 20);
  //Complex c = c1 + c2;
  //Complex c = c1 + 10;
  //Complex c = 10 + c1;
  Complex c;
  c = c1++;
  cout << c << endl;
  cout << c1 << endl;
  c = ++c2; 
  cout << c << endl;
  cout << c2 << endl;
  return 0;
}
