#include <iostream>
using namespace std;

class Tmp {
  public:
    Tmp(int id = 0) : _id(id) {}
    int getId() const {
      _id *= 2;
      return _id;
    }
  private:
    mutable int _id; // 声明为mutable的成员变量, 在const成员函数中可以改变
};
