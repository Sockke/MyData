#include <iostream>
#include <string>
using namespace std;

// 抽象类: 不能实例化对象, 但是可以定义指针或引用
// 当一个类不用来实例化对象, 但是需要它的指针或引用来指向派生类对象实现多态时, 将其是现成抽象类

class Car {
  public:
    Car(const string& name, double oil) : _name(name), _oil(oil) {}
    double showDistance() {
      return _oil / getFuelConsumpion();
    }
    string getName() const {
      return _name;
    }
  protected:
    virtual double getFuelConsumpion() = 0; // 该车的油耗
  protected:
    string _name;
    double _oil; // 剩余油量
};

class Bezn : public Car {
  public:
    Bezn(const string& name, double oil) : Car(name, oil) {}
    double getFuelConsumpion() {
      return 6.4;
    }
};
class BWM : public Car {
  public:
    BWM(const string& name, double oil) : Car(name, oil) {}
    double getFuelConsumpion() {
      return 7.2;
    }
};
class Audi : public Car {
  public:
    Audi(const string& name, double oil) : Car(name, oil) {}
    double getFuelConsumpion() {
      return 6.2;
    }
};

void show(Car& car) {
  cout << car.getName() << "可以跑" << car.showDistance() << "公里" << endl;
}

int main() {
  Bezn b1("奔驰", 50);
  BWM b2("宝马", 50);
  Audi a("奥迪", 50);
  show(b1);
  show(b2);
  show(a);
  return 0;
}
