#include <iostream>
#include <string>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h> 
using namespace std;

class TcpSocket {
  public:
    TcpSocket()
      : _sockfd(-1)
    {}
    // 创建套接字
    bool t_socket() {
      _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (_sockfd < 0) {
        return false;
      }
      return true;
    }
    // 绑定地址信息
    bool t_bind(const string& ip, unsigned short port) {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      addr.sin_port = htons(port);
      int len = sizeof(struct sockaddr_in);
      int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
      if (ret < 0) {
        return false;
      }
      return true;
    }
    // 开始监听, maxconnect是连接队列的最大数量
    // 限制了已完成连接的数量, 在Linux上一般为maxconnect+1
    // 如果连接队列已满, 则不受理其他的连接了
    bool t_listen(int maxconnect = 5) {
      int ret = listen(_sockfd, maxconnect);
      if (ret < 0) {
        return false;
      }
      return true;
    }
    // 客户端发起连接
    bool t_connect(const string& ip, unsigned short port) {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      addr.sin_port = htons(port);
      int len = sizeof(struct sockaddr_in);
      int ret = connect(_sockfd, (struct sockaddr*)&addr, len);
      if (ret < 0) {
        return false;
      }
      return true;
    }
    void setFd(int newfd) {
      _sockfd = newfd;
    }
    // 服务端获取新连接, 从已完成连接队列中, 去出一个连接,
    // 获取该连接的地址信息, 并分配一个新的描述符来标识这个客户端, 建立通信
    bool t_accept(TcpSocket& clisock) {
      struct sockaddr_in addr;
      socklen_t len = sizeof(struct sockaddr_in);
      int newfd = accept(_sockfd, (struct sockaddr*)&addr, &len);
      if (newfd < 0) {
        return false;
      }
      clisock.setFd(newfd);
      return true;
    }
    bool t_read(string& data) {
      char buf[1024] = {0};
      int ret = recv(_sockfd, buf, 1024, 0);
      if (ret < 0) {
        return false;
      } else if (ret == 0) {
        cout << "shutdown" << endl;
        return false;
      } else {
        data.assign(buf, ret);
        return true;
      }
    }
    bool t_send(const string& data) {
      int ret = send(_sockfd, &data[0], data.size(), 0);
      if (ret < 0) {
        return false;
      } else {
        return true;
      }
    }
    void t_close() {
      close(_sockfd);
      _sockfd = -1;
    }
  private:
    int _sockfd;
};
