#include <iostream>
#include <string>
using std::cout;
using std::endl;

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
      cout << "create a BENZ car:" << _name << endl;
    }
};

class Light {
  public:
    Light(const std::string type) : _type(type) {}
    virtual void show() = 0;
    std::string _type;
};
class BmwLighe : public Light {
  public:
    BmwLighe(const std::string& type) : Light(type) {}
    void show() {
      cout << "create a light:" << _type<< endl;
    }
};
class BenzLight : public Light {
  public:
    BenzLight(const std::string& type) : Light(type) {}
    void show() {
      cout << "create a light:" << _type << endl;
    }
};

enum FactoryType {
  BMW,
  BENZ
};
class AbstractFactory {
  public:
    AbstractFactory(FactoryType type) : _type(type) {}
    virtual Car* createCar(const std::string& name) = 0;
    virtual Light* createLight(const std::string& type) = 0;
    FactoryType _type;
};
class BmwFactory : public AbstractFactory {
  public:
    BmwFactory() : AbstractFactory(BMW) {}
    Car* createCar(const std::string& name) {
      return new Bmw(name);
    }
    Light* createLight(const std::string& type) {
      return new BmwLighe(type);
    }
};
class BenzFactory : public AbstractFactory {
  public:
    BenzFactory() : AbstractFactory(BENZ) {}
    Car* createCar(const std::string& name) {
      return new Benz(name);
    }
    Light* createLight(const std::string& type) {
      return new BenzLight(type);
    }
};

