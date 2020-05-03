#include <iostream>
using namespace std;

class sock {
  public:
    sock(int name = 1) : _name(name){}
    void common_func() {}
    virtual void virtual_func() {}
    static void static_func() {}
  private:
    int _name;
};

int main() {
  sock t;
  return 0;
}
