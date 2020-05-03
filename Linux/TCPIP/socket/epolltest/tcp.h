#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <unistd.h>
using namespace std;

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int BUF_SIZE = 10;
class TcpSocket {
  public:
    TcpSocket() : _fd(-1) {}
    void t_socket() {
      _fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      assert(_fd != -1);
      // 设置地址重用
      int opt = 1;
      setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(int));
    }
    void t_bind(const char* ip, unsigned short port) {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip);
      addr.sin_port = htons(port);
      int ret = bind(_fd, (struct sockaddr*)&addr, sizeof(addr));
      assert(ret != -1);
    }
    void t_listen(int maxconnect = 5) {
      int ret = listen(_fd, maxconnect);
      assert(ret != -1);
    }
    void t_connect(const char* ip, unsigned short port) {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip);
      addr.sin_port = htons(port);
      int ret = connect(_fd, (struct sockaddr*)&addr, sizeof(addr));
      assert(ret != -1);
    }
    int t_accept() {
      struct sockaddr_in addr;
      socklen_t len = sizeof(addr);
      int newfd = accept(_fd, (struct sockaddr*)&addr, &len);
      assert(newfd != -1);
      return newfd;
    }
    void t_recv(string& data) {
      char buf[BUF_SIZE] = {0};
      int cnt = recv(_fd, buf, BUF_SIZE-1, 0);
      if (cnt <= 0) {
        close(_fd);
      } else {
        data.assign(buf, cnt);
      }
    }
    void t_recv_nonblock(string& data) {
      while (1) {
        char buf[BUF_SIZE] = {0};
        int cnt = recv(_fd, buf, BUF_SIZE-1, 0);
        if (cnt < 0) {
          if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            cout << "read later" << endl;
            break;
          }
          close(_fd);
          break;
        } else if (cnt == 0) {
          close(_fd);
        } else {
          string tmp(buf);
          data += tmp;
        }
      }
    }
    void t_send(const string& data) {
      int cnt = send(_fd, &data[0], data.size(), 0);
      if (cnt < 0) {
        close(_fd);
      }
    }
    int getfd() const {
      return _fd;
    }
    void setfd(int newfd) {
      _fd = newfd;
    }
    
  private:
    int _fd;
};
