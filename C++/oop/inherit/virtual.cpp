#include <iostream>
#include <typeinfo>
using namespace std;

// 1. 什么是静态绑定:
// 在编译时期的函数调用.
// 比如说, p->show()  call Base::show(01612DAh), 
// 在编译时期就确定了是哪个作用域下的哪个函数的调用

// RTTI: run time type info 运行时的类型信息

// 2. 虚函数.
// a. 如果类里面定义了虚函数, 那么在编译时期, 编译器会为这个类创建一个唯一的vftable
// 虚函数表, 虚函数表中存储了RTTI指针, 偏移量以及虚函数的地址
// 在程序运行时, 所有的虚函数表都会被加载到.rodata段中.
// b. 如果类里面定义了虚函数, 那么这个类产生的对象中存储了vfptr虚函数表指针
// 和对应的成员变量. 但是这个虚函数表是该类的所有对象所共享的
// c. 如果类里面定义了虚函数, 派生类中有与基类虚函数完全相同的函数
// (返回值+函数名+参数列表), 那么该函数被视为虚函数, 并且覆盖基类对应的虚函数.
//
// 问题:
// 1. 类中虚函数的个数会不会影响对象内存的大小?
// 不会, 因为对象的内存中存储的是虚函数表指针和成员变量,
// 虚函数的个数只会影响虚函数表的大小
// 2. 派生类重写(覆盖)基类的虚函数, 那么会不会影响虚函数表的大小?
// 不会, 因为派生类重写的虚函数会将派生类继承过来的对应基类的虚函数地址覆盖掉
//
// 什么是静态绑定和动态绑定?
// 1. 静态绑定, 编译时期就确定调用哪个作用域下的哪个函数
// 2. 动态绑定, 运行时期才确定调用哪个作用域下的哪个函数
// 编译时期, 对于存在继承关系的成员函数的调用: Derive d; Base* b = &d; b->show();
// 先在基类中查看该函数的属性, 如果不是虚函数则直接生成call Base::show(), 属于静态绑定;
// 如果是虚函数, 则根据指向对象的虚函数表指针指向的虚函数表中指定函数的调用, 
// 生成mov eax,[b]; mov ecx,[eax];call ecx; call寄存器, 属于动态绑定
//
// 静态绑定的类型识别是在编译时期确定的
// 动态绑定的类型识别是在运行时期确定的


class Base {
  public:
    Base(int data = 10) : _ma(data) {}
    //virtual void show() const {
    //  cout << "Base show()" << endl;
    //}
    virtual void show() const {
      cout << "Base show(int)" << endl;
    }
  private:
    int _ma;
};
class Derive : public Base {
  public:
    Derive(int data) : Base(data), _mb(data) {}
    void show() const { // 覆盖/重写
      cout << "Derive show()" << endl;
    }
  private:
    int _mb;
};

int main() {
  //Base b;
  //Derive* d;
  //d = (Derive*)&b;
  //d->show();
  //cout << typeid(*d).name() << endl;
  Derive d(10);
  Base* b = &d;
  b->show();
  cout << typeid(b).name() << endl;
  cout << typeid(*b).name() << endl;
  return 0;
}

