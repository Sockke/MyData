#include <iostream>
using namespace std;

// 重载, 隐藏, 覆盖
// 1. 重载关系
// 一组函数重载, 必须在同一作用域下, 函数名相同, 参数列表不同
// 2. 隐藏关系
// 在继承关系中, 派生类中的函数名与基类函数名相同, 基类同名函数被隐藏.
// 在派生类中不能直接调用基类的隐藏函数, 必须加上作用域来调用

class Base {
  public:
    Base(int data = 10) : _ma(data) {}
    void show() const {
      cout << "Base show()" << endl;
    }
    void show(int) const {
      cout << "Base show(int)" << endl;
    }
    void print() const {
      cout << "Base print()" << endl;
    }
  private:
    int _ma;
};
class Derive : public Base {
  public:
    Derive(int data) : Base(data), _mb(data) {}
    void show() const {
      cout << "Derive show()" << endl;
    }
  private:
    int _mb;
};

int main() {
  Derive d(10);
  d.show();
  d.Base::show(5); // 基类同名函数被隐藏
  d.print();
  return 0;
}

// 继承关系中, 类型的转换: 只支持类型从下向上的转换
// 1. 基类对象 = 派生类对象: 可以, 发生切片, 将派生类继承基类的部分赋给基类对象
// 2. 派生类对象 = 基类对象: 不可以, 基类的作用域肯定比派生类小, 无法将基类赋给子类
// 3. 基类指针 = &派生类对象: 可以, 基类指针只能访问派生类从基类继承过来的部分
// 如果像访问派生类特有的部分, 需要进行类型强转 
// 4. 派生类指针 = &基类对象: 不可以, 基类对象的地址范围比派生类指针指向的范围小,
// 无法直接将基类对象地址赋给派生类指针.
// 可以进行类型强转, 但是可能会访问非法内存

#if 0
int main() {
  Base b;
  Derive d(5);
  //b = d;
  Base* bp = &d;
  ((Derive*)bp)->show(); // 访问派生类的show()
  Derive* dp = (Derive*)&b; // 可能会访问非法内存
  return 0;
}

#endif
