#include <iostream>
using namespace std;
#pragma pack(4)

// virtual的修饰:
// 1. 可以修饰成员方法, 表示虚函数
// 2. 可以修饰继承方式, 表示虚继承
//
// 抽象类与虚基类:
// 1. 抽象类: 存在纯虚函数的类
// 2. 虚基类: 被虚继承的类
//
// 多继承的优势和劣势:
// 1. 优势: 可以复用更多种类的代码, 可以重写更多种类的接口
// 2. 劣势: 会出现类似于菱形继承导致间接基类成员变量的多重继承(继承了多次)
//
// vbptr与vbtable: (virtual base)
// 1. 当派生类的继承方式为虚继承时, 该类会产生一个虚基类表vbtable
// 2. 当派生类的继承方式为虚继承时, 该类产生的对象会有一个虚基类指针vbptr, 
// 指向该类的vbtable
// 3. vbtable中存放着虚基类中继承过来的变量在对象内存中的偏移量
// 在vs和gcc下vbtable的布局有所差异, 在vs下偏移量在vbtable[1]中
// 在gcc下偏移量是vbtable[0]-vbtable[1]


#if 0
class A {
  public:
    A(int ma) : _ma(ma) {
      cout << "A()" << endl;
    }
  protected:
    int _ma;
};
class B : public A {
  public:
    B(int mb) : A(mb), _mb(mb) {
      cout << "B()" << endl;
    }
  private:
    int _mb;
};
class C : public A {
  public:
    C(int mc) : A(mc), _mc(mc) {
      cout << "C()" << endl;
    }
  private:
    int _mc;
};

class D : public B, public C {
  public:
    D(int md) : B(md), C(md), _md(md) {
      cout << "D()" << endl;
    }
  private:
    int _md;
};

int main() {
  D d(10); // 调用了2次A(), d对象的内存中继承过来了2个_ma成员变量
  cout << sizeof(D) << endl; // 20
  cout << sizeof(d) << endl; // 20
  return 0;
}
#endif

// 虚继承解决菱形继承导致的问题:
// 1. 需要进行多继承的派生类的直接基类需要通过虚继承
// 2. 虚继承使得需要多继承的派生类对象的内存结构发生改变, 
// 将之前出现重复继承的变量的地方被vbptr给替换掉, 同时重复继承的变量只出现一次放到最后
// 3. 可以通过指针来访问对象的vbptr指向的vbtable, 根据表中的偏移量来
// 对虚基类继承来的成员变量进行修改
class A {
  public:
    A(int ma) : _ma(ma) {
      cout << "A()" << endl;
    }
    int _ma;
};
class B : virtual public A {
  public:
    B(int mb) : A(mb), _mb(mb) {
      cout << "B()" << endl;
    }
  private:
    int _mb;
};
class C : virtual public A {
  public:
    C(int mc) : A(mc), _mc(mc) {
      cout << "C()" << endl;
    }
  private:
    int _mc;
};

class D : public B, public C {
  public:
    D(int md) : A(md), B(md), C(md), _md(md) {
      cout << "D()" << endl;
    }
  private:
    int _md;
};

int main() {
  D d(10);
  long long int* p = (long long int*)&d;
  p = (long long int*)(*p);
  char* q = (char*)&d;
  q += (*p - *(p + 1));
  int* ma = (int*)q;
  *ma = 20;
  cout << d._ma << endl;
  //cout << *ma << endl;
  //cout << sizeof(B) << endl;
  //cout << sizeof(C) << endl;
  return 0;
}
