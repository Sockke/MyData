#include <iostream>
#include <string>
using std::cout;
using std::endl;

// 工厂方法模式

class Car {
  public:
    Car(const std::string& name) : _name(name) {}
    virtual void show() = 0;
    std::string _name;
};

class Bmw : public Car {
  public:
    Bmw(const std::string& name) : Car(name) {}
    void show() {
      cout << "create a BMW car:" << _name << endl;
    }
};

class Benz : public Car {
  public:
    Benz(const std::string& name) : Car(name) {}
    void show() {
      cout << "create a Audi car:" << _name << endl;
    }
};


enum FactoryType {
  BMW,
  BENZ
};
class Factory {
  public:
    Factory(FactoryType type) : _type(type) {}
    virtual Car* createCar(const std::string& name) = 0;
    FactoryType _type;
};

class BMWFactory : public Factory {
  public:
    BMWFactory() : Factory(BMW) {}
    Car* createCar(const std::string& name) {
      return new Bmw(name);
    }
};

class BENZFactory : public Factory {
  public:
    BENZFactory() : Factory(BENZ) {}
    Car* createCar(const std::string& name) {
      return new Benz(name);
    }
};
