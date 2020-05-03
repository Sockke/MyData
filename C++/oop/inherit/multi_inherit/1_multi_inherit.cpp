#include <iostream>
using namespace std;

#if 0
class A
{
  public:
      A(int data) :ma(data) { cout << "A()" << endl;  }
        ~A() { cout << "~A()" << endl;  }
  //private:
          int ma;

};
class B : virtual public A
{
  public:
      B(int data) :A(data), mb(data) { cout << "B()" << endl;  }
        ~B() { cout << "~B()" << endl;  }
  private:
          int mb;

};
class C : virtual public A
{
  public:
      C(int data) :A(data), mc(data) { cout << "C()" << endl;  }
        ~C() { cout << "~C()" << endl;  }
  private:
          int mc;

};
////////////////////////////////////////
class D : public B, public C
{
  public:
    //“A::A”: 没有合适的默认构造函数可用
    D(int data) :A(data), B(data), C(data), md(data) 
  {
    cout << "D()" << endl;
  }
    ~D() { cout << "~D()" << endl;  }
  private:
    int md;
};

int main() {
  D d(10);
  cout << d.ma << endl;  
  int* p = (int*)&d;
  p = (int*)*p;
  //p++;
  int offset = *p;
  char* q = (char*)&d;
  q += offset;
  *((int*)q) = 20;
  cout << d.ma << endl;
  return 0;
}
#endif

// 多继承中, 构造函数的调用顺序: 虚基类, 普通基类, 成员变量, 该类的构造函数
