#include <iostream>
using namespace std;

// 对象的优化:
// Base b(10);
// Base b = 10;
// Base b = Base(10);
// 由于编译器的优化, 直接调用有一个参数的构造函数
// b = Base(10);
// b = (Base)10;
// b = 10;
// 显示或隐式构造临时对象, 然后赋值, 最后析构临时对象
// Base* b = &Base(10);
// 构造临时对象, 析构临时对象, 在gcc下不允许临时对象的地址作为右值赋给一个指针
// Base* b = new Base(10);
// 开辟内存空间, 构造对象
// const Base& b = Base(10);
// 构造临时对象, 但是不析构对象, 直到引用b出作用域后才析构

// 在函数调用返回对象的过程中, 考虑的优化规则:
// 1. 参数的传递优先按引用传递
// 2. 返回值优先按临时对象返回, 不要用已经定义过的局部对象返回
// 3. 接收时优先用初始化的方式接收, 不要按赋值接收

class Base {
  public:
    Base(int a = 10) : _a(a) {cout << "Base()" << endl;}
    ~Base() {cout << "~Base()" << endl;}
    Base(const Base& b) : _a(b._a) {cout << "Base(const Base&)" << endl;}
    Base& operator=(const Base& b) {
      _a = b._a;
      cout << "operator=" << endl;
      return *this;
    }
    int getData() const {
      return _a;
    }
  private:
    int _a;
};

// 最终的优化
Base getObj(Base& b) { 
  int val = b.getData();
  return Base(val); // 类似于Base b = Base(val), 由于编译器优化, 直接调用构造
}
int main() {
  Base b1;
  Base b2 = getObj(b1); // Base b2 = Base(val)
  // return Base(val) 如何知道b2的地址, 从而直接构造b2的?
  // 在进行函数调用之前, 不仅保存了b1的地址, b2的地址也保存了
  return 0;
}
#if 0
Base getObj(Base b) { // Base(const Base&)
  int val = b.getData();
  // 在gcc下直接进行了优化
  Base tmp(val); // Base()
  return tmp; // Base(const Base&)
}
// ~Base()
// ~Base()

int main() {
  Base b1; // Base()
  Base b2; // Base()
  b2 = getObj(b1); // operator=
  // ~Base()
  return 0;
}
// Base()
// Base()
#endif

#if 0
int main() {
  Base b1 = Base(10); // Base(10)
  Base b2 = 10; // Base(10)
  cout << "--------------------" << endl;
  b1 = Base(20); // Base(20), operator=, ~Base()
  b1 = (Base)30; // Base(30), operator=, ~Base()
  b1 = 40; // Base(40), operator=, ~Base()
  cout << "--------------------" << endl;
  const Base& b3 = Base(10); // Base(10)
  const Base& b4 = 10; // Base(10)
  //Base* b5 = &Base(10); // gcc下用指针保存临时对象的地址是不被允许的
  Base* b6 = new Base(10); // Base(10)
  delete b6; // ~Base()
  cout << "--------------------" << endl;
  return 0;
}
#endif
