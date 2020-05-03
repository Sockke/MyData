#include <iostream>
#include <string>
using std::cout;
using std::endl;

// 装饰器模式 -- 结构型设计模式

class Car {
  public:
    Car() {}
    Car(const std::string& name) : _name(name) {}
    virtual void show() = 0;
    std::string _name; 
};
class Bmw : public Car {
  public:
    Bmw(const std::string& name) : Car(name) {}
    void show() {
      cout << "这是一辆宝马汽车, 其配置有: 基本配置";
    }
};
class Benz : public Car {
  public:
    Benz(const std::string& name) : Car(name) {}
    void show() {
      cout << "这是一辆奔驰汽车, 其配置有: 基本配置";
    }
};

class Decorator1 : public Car {
  public:
    Decorator1(Car* car) : _car(car) {}
    void show() {
      _car->show();
      cout << ", 定速巡航";
    }
  private:
    Car* _car;
};
class Decorator2 : public Car {
  public:
    Decorator2(Car* car) : _car(car) {}
    void show() {
      _car->show();
      cout << ", 自动刹车";
    }
  private:
    Car* _car;
};
