#include <iostream>
#include <string>

// 简单工厂模式

enum carType{BENZ, BMW};

class Car {
  public:
    Car(const std::string& name) : _name(name){}
    virtual void show() = 0;
    std::string _name;
};

class Benz : public Car {
  public:
    Benz(const std::string& name) : Car(name) {}
    void show() {
      std::cout << "create a Benz car:" << _name << std::endl;
    }
};
class Bmw : public Car {
  public:
    Bmw(const std::string& name) : Car(name) {}
    void show() {
      std::cout << "create a Bmw car:" <<  _name << std::endl;
    }
};

class Factory {
  public:
    Car* createCar(carType type) {
      switch(type) {
        case BENZ:
          return new Benz("e300");
          break;
        case BMW:
          return new Bmw("x6");
          break;
        default:
          return nullptr;
          break;
      }
    }
};


