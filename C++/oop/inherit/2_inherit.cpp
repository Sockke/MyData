#include <iostream>
using namespace std;

// 派生类对象的构造与析构顺序:
// 1. 调用基类的构造函数, 构造从基类继承的成员
// 2. 调用自己的构造函数, 构造自己的成员
// 3. 调用自己的析构函数, 析构自己的成员
// 4. 调用基类的析构函数, 析构基类的成员

// 基类和派生类定义同名的函数, 构成隐藏 
// 如果想要调用, 需要在调用时加上作用域, 或者直接通过using来展开作用域
//
class Base {
  public:
    Base(int data)
      : _ma(data) 
    {
      cout << "Base()" << endl;
    }
    ~Base() {
      cout << "~Base()" << endl;
    }
  private:
    int _ma;
};

class Derive : public Base {
  public:
    Derive(int data)
      : Base(data)
      , _mb(data)
    {
      cout << "Derive()" << endl;
    }
    ~Derive() {
      cout << "~Derive()" << endl;
    }
  private:
    int _mb;
};

int main() {
  return 0;
}
