// 观察者模式 --- 带智能指针
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <memory>
using std::cout;
using std::endl;

class Listener {
  public:
    Listener(std::string name) : _name(name) {}
    virtual void handleMessage(int msgid) = 0;
    std::string _name;
};

class Listener1 : public Listener {
  public:
    Listener1(std::string name) : Listener(name) {}
    void handleMessage(int msgid) {
      switch(msgid) {
        case 1:
          cout << _name << " handle 1 message" << endl;
          break;
        case 2:
          cout << _name << " handle 2 message" << endl;
          break;
        case 3:
          cout << _name << " handle 3 message" << endl;
          break;
        default:
          break;
      }
    }
};
class Listener2 : public Listener {
  public:
    Listener2(std::string name) : Listener(name) {}
    void handleMessage(int msgid) {
      switch(msgid) {
        case 1:
          cout << _name << " handle 1 message" << endl;
          break;
        case 2:
          cout << _name << " handle 2 message" << endl;
          break;
        default:
          break;
      }
    }
};
class Listener3 : public Listener {
  public:
    Listener3(std::string name) : Listener(name) {}
    void handleMessage(int msgid) {
      switch(msgid) {
        case 2:
          cout << _name << " handle 2 message" << endl;
          break;
        default:
          break;
      }
    }
};

class Observer {
  public:
    void addHandler(std::weak_ptr<Listener> listener, int msgid) {
      _obser[msgid].push_back(listener);
      //auto curit = _obser.find(msgid);
      //if (curit == _obser.end()) {
      //  std::list<Listener*> newlist;
      //  newlist.push_back(listener);
      //  _obser.insert({msgid, newlist});
      //} else {
      //  curit->second.push_back(listener);
      //}
    }
    void removeHandler(std::weak_ptr<Listener> listener, int msgid) {
      // unordered_map<int, list<Listener*>>::iterator
      std::shared_ptr<Listener> sptr1 = listener.lock(); // 需要移除的资源已被释放
      if (sptr1 == nullptr) {
        return;
      }
      auto mit = _obser.find(msgid);
      if (mit == _obser.end()) {
        return;
      }
      std::list<std::weak_ptr<Listener>>& curlist = mit->second;
      auto lit = curlist.begin();
      while (lit != curlist.end()) {
        // weak_ptr没有重载==运算符
        //if (lit->lock() == listener.lock()) {
        //  curlist.erase(lit);
        //  return;
        //}
        std::shared_ptr<Listener> sptr2 = lit->lock();
        if (sptr2 == nullptr) {
          lit = curlist.erase(lit);
        } else {
          if (sptr1 == sptr2) {
            curlist.erase(lit);
            return;
          }
          ++lit;
        }
      }
    }
    void dispatch(int msgid) {
      auto mit = _obser.find(msgid);
      if (mit == _obser.end()) {
        return;
      }
      std::list<std::weak_ptr<Listener>>& curlist = mit->second;
      auto lit = curlist.begin();
      while (lit != curlist.end()) {
        std::shared_ptr<Listener> sptr = lit->lock();
        if (sptr == nullptr) {
          lit = curlist.erase(lit);
        } else {
          sptr->handleMessage(msgid);
          ++lit;
        }
      }
    }
  private:
    std::unordered_map< int, std::list<std::weak_ptr<Listener>> > _obser;
};
