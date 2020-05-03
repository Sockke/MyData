#include <iostream>
using namespace std;

// 类型重载:
// 没有返回值, 没有参数

class Tmp {
  public:
    Tmp(int a) : _a(a) {}
    // 类型重载
    operator int() {
      return _a;
    }
  private:
    int _a;
};

int main() {
  Tmp t(1);
  //int a = *(int*)&t;
  int a = t;
  cout << a << endl;
  return 0;
}
