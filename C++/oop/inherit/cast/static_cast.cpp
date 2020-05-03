#include <iostream>
using namespace std;

class Base {
  public:
    Base(int ma) : _ma(ma) {}
    int _ma;
};
class Derive : public Base {
  public:
    Derive(int mb) : Base(mb), _mb(mb) {}
    int _mb;
};

int main() {
  int a = 10;
  int* p = static_cast<int*>(&a);
  cout << "*p = " << *p << endl;

  Base b(10);
  Derive* dp = static_cast<Derive*>(&b);
  cout << "Derive:mb=" << dp->_mb << endl;
  return 0;
}
