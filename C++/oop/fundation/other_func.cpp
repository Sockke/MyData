#include <iostream>
#include <string>
using namespace std;

// 普通成员方法:
// 1. 调用该方法时需要依赖一个对象, 因为在编译时期编译器为每个普通的成员方法都添加了this指针
// 2. 普通成员方法可以访问对象的任意成员变量和方法
//
// 静态成员方法
// 1. 调用该方法时不需要依赖对象, 直接通过类名+类域来访问, 因为在编译时期编译器不会为静态成员
// 方法添加this指针
// 2. 静态成员方法只能访问静态的成员变量和方法
//
// 常成员方法
// 1. 调用该方法时需要依赖对象, 该对象可以是普通对象, 也可以是常对象
// 2. 常成员方法只能读取任意成员变量但不能修改, 只能调用常方法

// 为什么要将只读的成员方法设置为常方法?
// 1. 对于只读的成员方法, 设置为常方法之后, 在编译时期会为常成员方法添加const修饰的this指针
// 2. 无论是普通对象还是常对象, 都可以访问常成员方法. 常对象是无法访问普通成员方法的, 这是因为
// 无法将常对象的指针赋给一个普通的this指针

class Date {
  public:
    Date(int year, int month, int day)
      : _year(year)
      , _month(month)
      , _day(day) {}
    void show() const {
      cout << _year << "/" << _month << "/" << _day << endl;
    }
  private:
    int _year;
    int _month;
    int _day;
};

class Goods {
  public:
    Goods(const string& name, int year, int month, int day)
      : _name(name)
      , _date(year, month, day) 
    {
      ++counts;
    }
    static int getCounts() {
      return counts;
    }
    void show() const {
      cout << "name:" << _name << endl;
      _date.show();
    }
  private:
    string _name;    
    Date _date;
    static int counts; // 声明
};
int Goods::counts = 0; // 需要在类外定义

int main() {
  Goods goods1("商品1", 2019, 11, 16);
  Goods goods2("商品2", 2019, 11, 16);
  Goods goods3("商品3", 2019, 11, 16);
  Goods goods4("商品4", 2019, 11, 16);
  const Goods good5("镇店之宝", 1998, 11, 1);

  good5.show();
  cout << "goods nums:" << Goods::getCounts() << endl;
  return 0;
}
