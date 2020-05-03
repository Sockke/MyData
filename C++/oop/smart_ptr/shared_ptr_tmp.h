#include <iostream>
#include <memory>
using namespace std;

//class B;
//class A {
//  public:
//    A() {cout << "A()" << endl;}
//    ~A() {cout << "~A()" << endl;}
//    shared_ptr<B> _sptrb; 
//};
//class B {
//  public:
//    B() {cout << "B()" << endl;}
//    ~B() {cout << "~B()" << endl;}
//    shared_ptr<A> _sptra;
//};

// 使用weak_ptr解决shared_ptr交叉引用的问题
class B;
class A {
  public:
    A() {cout << "A()" << endl;}
    ~A() {cout << "~A()" << endl;}
    int sum(int a, int b) {
      return a = b;
    }
    weak_ptr<B> _wptrb; 
};
class B {
  public:
    B() {cout << "B()" << endl;}
    ~B() {cout << "~B()" << endl;}
    void func() {
      //shared_ptr<A> sptr(_wptra);
      shared_ptr<A> sptr = _wptra.lock();
      if (sptr != nullptr) { // weak_ptr提升成强智能指针可能会失败, 因为存在资源已经释放的情况
        cout << sptr->sum(10, 20) << endl;
      }
    }
    weak_ptr<A> _wptra;
};



