#include <iostream>
using namespace std;

// 指向成员的指针
// 指向成员变量的指针:
// 1. 指向普通成员变量的指针: int Tmp::*p = &Tmp::_id;
// 普通成员变量依赖于对象, 需要通过对象来进行操作: t.*p = 100
// 2. 指向静态成员变量的指针: int *p = &Tmp::allid;
// 静态成员变量不依赖于对象, 直接通过普通的指针直接进行操作 *p = 100
//
// 指向成员函数的指针:
// 1. 指向普通成员函数的指针: void(Tmp::*show)() = &Tmp::showId; // 必须取地址, 来防止this参数的影响
// 普通成员函数依赖于对象, 需要通过对象来进行操作: (t.*show)()
// 2. 指向静态成员函数的指针: void(*show)() = Tmp::showAllId;  
// 静态成员函数不依赖于对象, 直接通过普通的函数指针直接进行操作 show()

class Tmp {
  public:
    void showId() {
      cout << "id:" << _id << endl;
    } 
    static void showAllId() {
      cout << "allid:" << allid << endl;
    }
    int _id;
    static int allid;
};
int Tmp::allid = 0;

int main() {
#if 0
  Tmp t;
  int Tmp::*p = &Tmp::_id; 
  t.*p = 100;
  cout << "id:" << t.*p << endl;
#endif
#if 0
  int* p = &Tmp::allid;
  *p = 100;
  cout << "allid:" << *p << endl;
#endif
#if 0
  Tmp t;
  void (Tmp::*show)() = &Tmp::showId;
  (t.*show)();
#endif
#if 0
  void (*show)() = Tmp::showAllId;
  show();
#endif
  Tmp* t = new Tmp();
  //int Tmp::*p = &Tmp::_id;
  //t->*p = 100;
  //cout << "id:" << t->*p << endl;
  //delete t;
  void (Tmp::*show)() = &Tmp::showId;
  (t->*show)(); 
  return 0;
}
