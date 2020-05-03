#include <iostream>
#include <cstring>
using namespace std;

// 考察vftable什么时候放入vfptr中的
// vftable在对象开辟空间之后, 存入vfptr中的
class Base {
  public:
    Base() {
      cout << "Base()" << endl;
      clear();
    }
    void clear() {
      memset(this, 0, sizeof(*this));
    }
    virtual void show() {cout << "Base::show()" << endl;}
};
class Derive : public Base {
  public:
    Derive() {
      cout << "Derive()" << endl;
    }
    void show() {cout << "Derive::show()" << endl;}
};

int main() {
  Base b;
  Derive d;
  Derive* de = (Derive*)&b;
  de->show();
  //Base* base = new Base();
  //base->show();
  //delete base;
  // Base构造函数中, 将vfptr给清除了, 因此找不到Base的show()方法, 段吐核
  //Derive* derive = new Derive();
  //derive->show();
  //delete derive;
  // Derive构造之前先调用Base的构造函数, 将Base的vfptr清空,
  // 然后在构造Derive之前将Derive的vftable放入vfptr中,
  // 构造完成后调用Derive的show方法
  return 0;
}

#if 0
// 考察访问限定符的检查时期
// 对于访问限定符的限制, 是检查指针或引用变量类型中该函数的访问限定符.
// 如果能访问并且发生动态绑定, 那么函数的确定执行是在运行时期, 此时不受访问限定符限制
class Base {
  public:
    virtual void show() {cout << "Base::show()" << endl;};
};
class Derive : public Base {
  private:
    void show() {cout << "Derive::show()" << endl;};
};

int main() {
  Base* base = new Derive();
  base->show();
  // 编译时期, 查看Base类中的show(), 发现是public可以访问, 并且发现是virtual函数,
  // 因此发生动态绑定, 取Derive对象前4个字节得到vfptr, 并找到vftable, 然后call eax
  // 来调用派生类的虚函数show.
  // 运行时期不进行访问限定符的检查, 当指令执行到call eax时, 直接调用派生类的show,
  // 不受访问限定符的限制
  return 0;
}
#endif

#if 0
// 考察了动态绑定和参数压栈时机
class A{
  public:    
    virtual void func(int val = 1)    { 
      std::cout<<"A->"<<val <<std::endl; 
    }    
    virtual void test()    { 
      // push 1
      func(); 
    }
};
class B : public A{
  public:    
    void func(int val=0){
      std::cout<<"B->"<<val <<std::endl;
    }
};

int main(int argc ,char* argv[]){    
  B*p = new B;    
  p->test();
  return 0; 
}
#endif
