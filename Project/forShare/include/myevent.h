#include <event.h>
#include <unordered_map>

/*
  对libevent中的IO框架库进行封装
  libevent是用C语言编写的高性能事件通知框架库 
  被广泛应用于一些底层的网络框架库, 比如说memcached
  它主要包含4大组件:
  1. 事件源, 比如说IO事件, 信号, 定时器
  2. 事件多路分发器, 底层基于IO复用技术对事件进行等待和事件分发
  3. 事件处理器, 底层主要定义了对应时间的处理函数
  4. Reactor, IO框架库的核心, 用来组织添加事件, 移除事件, 事件循环这些方法
*/

class Event {
  public:
    // 初始化event_base, 初始化Reactor实例
    Event();
    void add(int sockfd, void(*func_cb)(int, short, void*)); // 注册并添加事件
    void del(int sockfd); // 移除事件
    void wait(); // 事件循环
    // 将socket与缓冲事件关联起来
    void addBuf(int sockfd, void(*read_cb)(struct bufferevent*, void*)
        , void(*error_cb)(struct bufferevent*, short, void*));
  private:
    struct event_base* _base;
    std::unordered_map<int, struct event*> _events;
};
