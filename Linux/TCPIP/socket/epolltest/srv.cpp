#include "tcp.h"
#include <sys/epoll.h>
#include <fcntl.h>
#include <vector>

/*
epoll的LT与ET模式.
1. LT是电平触发, 是epoll默认的触发方式, 以EPOLLIN为例, 只要有事件到来, 就会触发EPOLLIN
ET是边沿触发, 是更高效的触发方式, 当有事件到来时, 只会出发一次, 因此需要搭配非阻塞socket来实现
对数据的全部读取, 相比于LT来讲, 大大减少了触发的次数.
2. 在多线程环境下, ET还是可能会触发多次的, 比如说当有事件到来时, 触发线程A来进行处理.
在处理过程中, 该事件有有新数据, 可能会触发线程B来进行处理. 同一事件触发多次.
可以通过EPOLLONESHORT选项来解决, 保证同一个事件只被一个线程进行处理.
*/

const int MAX_EPOLL = 10;
class Epoll {
  public:
    Epoll() : _epollfd(-1) {
      _epollfd = epoll_create(MAX_EPOLL);
      assert(_epollfd != -1);
    }

    void addfd(int fd, bool enable_et = false) {
      struct epoll_event ev;
      ev.events = EPOLLIN;
      ev.data.fd = fd;
      if (enable_et) {
        ev.events |= EPOLLET;
      }
      epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &ev);
      setnonblocking(fd);
    }
    void wait(vector<int>&fds, int timeout = 3000) {
      struct epoll_event evs[MAX_EPOLL];
      int cnt = epoll_wait(_epollfd, evs, MAX_EPOLL, timeout);
      assert(cnt > 0);
      if (cnt == 0) {
        cout << "timeout" << endl;
      } else {
        for (int i = 0; i < cnt; ++i) {
          int fd = evs[i].data.fd;
          fds.push_back(fd);
        }
      }
    }
    int getfd() const {return _epollfd;}
  private:
    void setnonblocking(int fd) {
      int old_flag = fcntl(fd, F_GETFL, 0);
      fcntl(fd, F_SETFL, old_flag | O_NONBLOCK);
    }
    int _epollfd;
};

class Server {
  public:
    Server(const char* ip, unsigned short port) {
      s.t_socket();
      s.t_bind(ip, port);
      s.t_listen();
    }
    void start() {
      p.addfd(s.getfd(), true);
      struct epoll_event evs[MAX_EPOLL];
      while (1) {
        int cnt = epoll_wait(p.getfd(), evs, MAX_EPOLL, -1);
        if (cnt < 0) {
          return;
        }
        et(evs, cnt, s.getfd());
      }
    }
  private:
    void lt(struct epoll_event* evs, int cnt, int listenfd) {
      for (int i = 0; i < cnt; ++i) {
        int sockfd = evs[i].data.fd;
        if (sockfd == listenfd) {
          int connfd = s.t_accept();
          p.addfd(connfd, false);
        } else if (evs[i].events & EPOLLIN) {
          TcpSocket cli;
          cli.setfd(sockfd);
          string data;
          cli.t_recv(data);
          cout << "srv get info:" << data << endl;
        } else {
          cout << "something else happened" << endl;
        }
      }
    }
    void et(struct epoll_event* evs, int cnt, int listenfd) {
      for (int i = 0; i < cnt; ++i) {
        int sockfd = evs[i].data.fd;
        if (sockfd == listenfd) {
          int connfd = s.t_accept();
          p.addfd(connfd, true);
        } else if (evs[i].events & EPOLLIN) {
          TcpSocket cli;
          cli.setfd(sockfd);
          string data;
          cli.t_recv_nonblock(data);
          cout << "srv get info:" << data << endl;
        } else {
          cout << "something else happened" << endl;
        }
      }
    }

    Epoll p;
    TcpSocket s; 
};

int main() {
  Server s("192.168.163.99", 9000);
  s.start();
  return 0;
}
