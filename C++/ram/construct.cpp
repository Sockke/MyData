#include <iostream>
using namespace std;
/*
  使用new来创建一个对象时, 如果构造函数中发生异常, 会不会导致内存泄漏
  1. 不会, 因为如果说构造对象失败, 预先开辟的内存会被操作系统进行回收, 可以通过valgrind来查看
  2. 如果说new中执行了malloc, 但是返回起始地址之前发生了异常, 会导致内存泄漏
*/
class Tmp {
  public:
    Tmp(int a) : _a(a) {
      cout << "Tmp()" <<endl;
      //throw "construct exception";
    }
    ~Tmp() {cout << "~Tmp()" << endl;}
    void* operator new(size_t size) {
      cout << "new" << endl;
      void* ptr = malloc(size);
      throw "new exception";
      return ptr;
    }
  private:
    int _a;
};

int main() {
  try {
    Tmp* t = new Tmp(10);
  } catch(const char* e) {
    cout << e << endl;
  }
  return 0;
}
