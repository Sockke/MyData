#include <iostream>
using namespace std;

// 哪些函数不能实现成虚函数?
//
// 实现成虚函数的条件:
// 1. 有对象, 对象中vfptr指向的vftable中存放着虚函数的地址
// 2. 有地址, 虚函数的地址放在vftable中
//
// 构造函数: 不可以的
// 1. 构造函数完成之前, 还没有产生对象
// 2. 构造函数中调用的函数都是静态绑定
//
// static函数: 不可以的
// 1. static函数不依赖对象
//
// 析构函数: 可以的
// 1. 析构函数调用的时候, 对象是存在的
//
// 什么时候需要将析构函数实现成虚析构函数?
// 当基类的指针或引用指向堆上开辟的派生类对象时, 在delete基类指针时, 
// 必须发生动态绑定, 否则派生类的析构函数无法调用, 造成内存泄漏

#if 0
class Base {
  public:
    Base(int ma) : _ma(ma){
      cout << "Base()" << endl;
    }
    ~Base() {
      cout << "~Base()" << endl;
    }
    virtual void show() {cout << "Base show()" << endl;}
  private:
    int _ma;
};
class Derive : public Base{
  public:
    Derive(int mb) : Base(mb), _mb(mb) {
      cout << "Derive()" << endl;
    }
    ~Derive() {
      cout << "~Derive()" << endl;
    }
    void show() {
      cout << "Derive show()" << endl;
    }
  private:
    int _mb;
};

int main() {
  Base* base = new Derive(10);
  base->show();
  delete base;  
  // 基类中的析构函数是普通函数, 因此发生静态绑定, 调用基类的析构函数
  // 没有调用派生类的析构函数, 如果派生类中有成员指针指向外部资源, 那么也无法释放
  return 0;
}
#endif

class Base {
  public:
    Base(int ma) : _ma(ma){
      cout << "Base()" << endl;
    }
    virtual ~Base() {
      cout << "~Base()" << endl;
    }
    virtual void show() {cout << "Base show()" << endl;}
  private:
    int _ma;
};
class Derive : public Base{
  public:
    Derive(int mb) : Base(mb), _mb(mb) {
      cout << "Derive()" << endl;
    }
    // 基类析构函数实现成虚析构函数, 派生类的析构函数自动实现成虚析构函数
    // 派生类的虚析构函数覆盖了父类的虚析构函数(虽然函数名不同)
    ~Derive() {
      cout << "~Derive()" << endl;
    }
    void show() {
      cout << "Derive show()" << endl;
    }
  private:
    int _mb;
};

int main() {
  Base* base = new Derive(10);
  base->show();
  delete base;
  //当调用Base的析构函数时, 发现Base的析构函数是虚析构函数, 因此发生动态绑定
  //访问指向对象的前4个字节vfptr, 找到vftable, 调用派生类的虚析构函数
  //调用完成之后, 再调用基类的虚析构函数
  return 0;
}
