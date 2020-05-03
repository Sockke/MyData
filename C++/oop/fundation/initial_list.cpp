#include <iostream>
#include <string>
using namespace std;

// 为什么需要初始化列表
// 1. 方便的去构造类中的成员对象
// 2. 提高构造成员对象的效率(直接构造, 少了赋值操作)

// 初始化列表初始化与构造函数体内初始化的区别
// 1. 初始化列表初始化, 直接在定义时初始化; 构造函数体内初始化是先定义, 后赋值
// 2. 初始化内置类型时, 在底层的汇编指令是一样的
// 3. 初始化自定义类型的成员对象时, 初始化列表直接构造, 函数体内初始化是先构造, 后赋值.
// 因此初始化列表初始化成员对象时能提高效率
//
// 初始化列表初始化的顺序:
// 初始化列表初始化的顺序, 是成员变量或成员对象设计的顺序

#if 0
class Date {
  public:
    Date(int year, int month, int day) {
      _year = year;
      _month = month;
      _day = day;
    }
    void show() {
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
      , _date(year, month, day) {}
    void show() {
      cout << "name:" << _name << endl;
      _date.show();
    }
  private:
    string _name;
    Date _date;
};

int main() {
  Goods g("火龙果", 2019, 11, 15);
  g.show();
  return 0;
}
#endif
