#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
using namespace std;

#if 0
/*
  单例模式, 饿汉与懒汉模式
*/
class Base{
  public:
    static Base* getInstance() {
      return &_base;
    }
  private:
    Base() {cout << "Base()" << endl;}
    Base(const Base&) = delete;
    Base& operator=(const Base&) = delete;
    static Base _base;
};
Base Base::_base;

class Base2 {
  public:
    static Base2* getInstance() {
      static Base2 base;
      return &base;
    }
  private:
    Base2() {cout << "Base2()" << endl;}
    Base2(const Base2&) = delete;
    Base2& operator=(const Base2&) = delete;
};
#endif

#if 0
/*
  工厂方法
*/
class Car {
  public:
    Car(const string& name) : _name(name) {}
    virtual void show() = 0;
  protected:
    string _name;
};
class Benz : public Car {
  public:
    Benz(const string& name) : Car(name) {}
    void show() {
      cout << "Benz car " << _name << endl;
    }
};
class Audi : public Car {
  public:
    Audi(const string& name) : Car(name) {}
    void show() {
      cout << "Audi car " << _name << endl;
    }
};
class Light {
  public:
    Light(const string& name) : _name(name) {}
    virtual void show() = 0;
  protected:
    string _name;
};
class BenzLight : public Light {
  public:
    BenzLight(const string& name) : Light(name) {}
    void show() {
      cout << "Benz light " << _name << endl;
    }
};
class AudiLight : public Light {
  public:
    AudiLight(const string& name) : Light(name) {}
    void show() {
      cout << "Audi light " << _name << endl;
    }
};

class Factory {
  public:
    virtual Car* createCar(const string& name) = 0;
    virtual Light* createLight(const string& name) = 0;
};
class BenzFactory : public Factory {
  public:
    Car* createCar(const string& name)  {
      return new Benz(name);
    }
    Light* createLight(const string& name) {
      return new BenzLight(name);
    }
};
class AudiFactory : public Factory {
  public:
    Car* createCar(const string& name) {
      return new Audi(name);
    }
    Light* createLight(const string& name) {
      return new AudiLight(name);
    }
};
#endif

#if 0
/*
  观察者监听者模式
*/
class Listener {
  public:
    Listener(const string& name) : _name(name) {}
    virtual void process_cb(int msg) = 0;
  protected:
    string _name;
};
class Listener1 : public Listener {
  public:
    Listener1(const string& name) : Listener(name) {}
    void process_cb(int msg) {
      switch(msg) {
        case 0:
          cout << _name << "-0" << endl;
          break;
        case 1:
          cout << _name << "-1" << endl;
          break;
        case 2:
          cout << _name << "-2" << endl;
          break;
      }
    }
};
class Listener2 : public Listener {
  public:
    Listener2(const string& name) : Listener(name) {}
    void process_cb(int msg) {
      switch(msg) {
        case 0:
          cout << _name << "-0" << endl;
          break;
        case 2:
          cout << _name << "-2" << endl;
          break;
      }
    }
};
class Observer {
  public:
    void reg(Listener* listener, int msg) {
      _map[msg].push_back(listener);
    }
    void notify(int msg) {
      auto it = _map.find(msg);
      if (it == _map.end()) {
        return;
      }
      list<Listener*>& l = it->second;
      auto lit = l.begin();
      while (lit != l.end()) {
        (*lit)->process_cb(msg);
        ++lit;
      }
    }
  private:
    unordered_map<int, list<Listener*>> _map;
};
#endif

#if 0
/*
  代理设计模式
*/
class Video {
  public:
    virtual void watch_free_movie() = 0;
    virtual void watch_vip_movie() = 0;
};
class WatchMovie : public Video{
  public:
    void watch_free_movie() {
      cout << "你正在观看免费电影" << endl;
    }
    void watch_vip_movie() {
      cout << "你正在观看VIP电影" << endl;
    }
};

class FreeProxy : public Video{
  public:
    FreeProxy() : _video(new WatchMovie()) {}
    void watch_free_movie() {
      _video->watch_free_movie();
    }
    void watch_vip_movie() {
      cout << "你不是VIP" << endl;
    }
  private:
    Video* _video;
};
class VIPProxy : public Video {
  public:
    VIPProxy() : _video(new WatchMovie()) {}
    void watch_free_movie() {
      _video->watch_free_movie();
    }
    void watch_vip_movie() {
      _video->watch_vip_movie();
    }
  private:
    Video* _video;
};
#endif

#if 0
/*
  装饰器模式
*/
class Car {
  public:
    Car(const string& name) : _name(name) {}
    virtual void show() = 0;
    string _name;
};
class Benz : public Car {
  public:
    Benz(const string& name) : Car(name) {}
    void show() {
      cout << "普通奔驰" << _name << endl;
    }
};

class Decorator1 : public Car {
  public:
    Decorator1(Car* car) 
      : Car(car->_name)
      ,_car(car) 
    {}
    void show() {
      _car->show();
      cout << ", 安装了定速巡航" << endl;
    }
  private:
    Car* _car;
};
class Decorator2 : public Car {
  public:
    Decorator2(Car* car)
      : Car(car->_name)
      , _car(car) 
    {}
    void show() {
      _car->show();
      cout << ", 安装了监视系统" << endl;
    } 
  private:
    Car* _car;
};
#endif

/*
  适配器模式
  通过电脑来连接投影仪, 需要中间的接口转换
*/
class VGA {
  public:
    virtual void show() = 0;
};
class VGAWire : public VGA{
  public:
    void show() {
      cout << "支持VGA接口" << endl;
    }
};
class HDMI {
  public:
    virtual void show() = 0;
};
class HDMIWire : public HDMI {
  public:
    void show() {
      cout << "支持HDMI接口" << endl;
    }
};

// 只支持VGA接口
class Computer {
  public:
    Computer(VGA* wire) : _wire(wire) {}
    void show() {
      _wire->show();
    }
  private:
    VGA* _wire;
};

class HDMITOVGA : public VGA {
  public:
    HDMITOVGA(HDMI* wire)
      : _wire(wire) {}
    void show() {
      _wire->show();
    }
  private:
    HDMI* _wire;
};
