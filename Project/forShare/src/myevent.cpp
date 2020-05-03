#include "../include/myevent.h"

// 初始化event_base, 生成Reactor实例
Event::Event() {
  _base = event_base_new();
}

// 创建事件处理器
// 将事件添加到事件多路分发器中, 将事件处理器添加到事件队列中,
// 建立事件与事件处理器之间的映射
void Event::add(int sockfd, void(*func_cb)(int, short, void*)) {
  struct event* ev = event_new(_base, sockfd, EV_READ | EV_PERSIST, func_cb, nullptr);
  event_add(ev, nullptr);
  _events.insert({sockfd, ev});
}

// 移除事件
void Event::del(int sockfd) {
  auto it = _events.find(sockfd);
  if (it == _events.end()) {
    return;
  }
  event_free(it->second);
  _events.erase(it);
}

// 事件循环
void Event::wait() {
  event_base_dispatch(_base);
}

void Event::addBuf(int sockfd, void(*read_cb)(struct bufferevent*, void*)
    , void(*error_cb)(struct bufferevent*, short, void*)) {
  // 定义缓冲区事件结构, 建立sockfd与缓冲事件的映射
  struct bufferevent* bev = nullptr;
  bev = bufferevent_socket_new(_base, sockfd, BEV_OPT_CLOSE_ON_FREE);
  // 为缓冲事件注册读事件以及error事件
  bufferevent_setcb(bev, read_cb, nullptr, error_cb, nullptr);
  // 将缓冲区事件添加到监听队列
  bufferevent_enable(bev, EV_READ | EV_WRITE);
}
