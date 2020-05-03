#include <iostream>
using namespace std;

// 继承的本质:
// 1. 代码的复用, 派生类从基类继承了所有成员, 并继承了作用域
//
// 访问限定的特点:
// 1. 一个类里面的成员定义成private, 在派生类中是不可见的, 能继承但不能访问
// 2. protected与private, protected成员在派生类中能访问, 外部不能访问;
// private成员在派生类和外部都不能直接访问
//
// struct与class的区别:
// 1. 类的默认访问权限不同
// 2. 类的默认继承方式不同
//
//
// 组合与继承的区别?
// 1. 组合是has a/a part of
// 2. 继承是is a/a kind of

class A {
  public:
    A(int a = 10) : _a(a) {cout << "A()" << endl;}
    void show() {cout << "A::show()" << endl;};
    void show(int) {cout << "A::show(int)" << endl;}
    int _a;
  protected:
    int _b;
  private:
    int _c;
};
class B : private A {
  B() : A(1)
  {
    cout << _a << endl;
  }
  void show() {cout << "B::show()" << endl;};
};

int main() {
  return 0;
}
