#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
using std::cout;
using std::endl;

class Listener {
  public:
    Listener(const std::string& name) : _name(name) {}
    virtual void handle(int msg) = 0;
  protected:
    std::string _name;
};
class Listener1 : public Listener {
  public:
    Listener1(const std::string& name) : Listener(name) {}
    void handle(int msg) {
      switch(msg) {
        case 1:
          cout << _name << " recv 1 msg!" << endl;
          break;
        case 2:
          cout << _name << " recv 2 msg!" << endl;
          break;
        default:
          break;
      }
    }
};
class Listener2 : public Listener {
  public:
    Listener2(const std::string& name) : Listener(name) {}
    void handle(int msg) {
      switch(msg) {
        case 2:
          cout << _name << " recv 2 msg!" << endl;
          break;
        default:
          break;
      }
    }
};
class Listener3 : public Listener {
  public:
    Listener3(const std::string& name) : Listener(name) {}
    void handle(int msg) {
      switch(msg) {
        case 1:
          cout << _name << " recv 1 msg!" << endl;
          break;
        case 3:
          cout << _name << " recv 3 msg!" << endl;
          break;
        default:
          break;
      }
    }
};

class Observer {
  public:
    // 订阅
    void subscribe(Listener* listener, int msg) {
      _obserMap[msg].push_back(listener);
    }
    // 发布
    void publish(int msg) {
      std::unordered_map<int, std::list<Listener*>>::iterator uit = _obserMap.find(msg);
      if (uit == _obserMap.end()) {
        return;
      }
      for (auto& e : uit->second) {
        e->handle(msg);
      }
    }
    // 移除
    void cancel(Listener* listener, int msg) {
      auto uit = _obserMap.find(msg);
      if (uit == _obserMap.end()) {
        return;
      }
      auto lit = uit->second.begin();
      while (lit != uit->second.end()) {
        if (*lit == listener) {
          uit->second.erase(lit);
          break;
        }
        ++lit;
      }
    }
  private:
    std::unordered_map<int, std::list<Listener*>> _obserMap;
};
