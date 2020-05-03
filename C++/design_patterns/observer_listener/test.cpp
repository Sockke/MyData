#include "observer.h"

// 观察者模式(发布-订阅模式), 即一组监听对象依赖一个观察对象的通知
//
// 观察者模式中, 有2个重要的角色, 分别是监听者和观察者(订阅者和发布者)
// 监听者订阅消息后进行等待, 观察者根据到来的消息通知给指定的监听者
// 因此在监听者类中有消息的处理, 在观察者类中有消息的订阅及消息的发布, 消息的移除

int main() {
  Listener* p1 = new Listener1("sock");
  Listener* p2 = new Listener2("liuchen");
  Listener* p3 = new Listener3("laoma");
  Observer q;
  q.subscribe(p1, 1);
  q.subscribe(p1, 2);
  q.subscribe(p2, 2);
  q.subscribe(p3, 1);
  q.subscribe(p3, 3);
  int msg = 0;
  for (;;) {
    cout << "发布的消息:";
    std::cin >> msg;
    if (msg == -1) {
      break;
    }
    q.publish(msg);
  }
  return 0;
}

#if 0
#include "power_observer.h"
#include <chrono> // C++中的时间类
#include <thread>

int main() {
  Observer q;
  std::shared_ptr<Listener> p1(new Listener1("sock"));
  std::shared_ptr<Listener> p2(new Listener2("liuchen"));
  {
  std::shared_ptr<Listener> p3(new Listener3("laoma"));
  //std::weak_ptr<Listener> wp1(p1);
  //std::weak_ptr<Listener> wp2(p2);
  //std::weak_ptr<Listener> wp3(p3);
  q.addHandler(p1, 1);
  q.addHandler(p1, 2);
  q.addHandler(p1, 3);
  q.addHandler(p2, 1);
  q.addHandler(p2, 2);
  q.addHandler(p3, 2);
  std::thread t([&](){
      int msgid = 0;
      while (std::cin >> msgid) {
        q.dispatch(msgid);
      }
  });
  t.detach();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  }
  std::this_thread::sleep_for(std::chrono::seconds(100));
  return 0;
}
#endif
