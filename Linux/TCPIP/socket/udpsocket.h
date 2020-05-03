#include <iostream>
#include <string>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

class UdpSocket {
  public:
    UdpSocket() 
      : _sockfd(-1)
    {}
    bool u_socket() {
      _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
      if (_sockfd < 0) {
        return false;
      }
      return true;
    }
    bool u_bind(const string& ip, unsigned short port) {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip.c_str()) ;
      addr.sin_port = htons(port);
      int len = sizeof(struct sockaddr_in);
      int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
      if (ret < 0) {
        return false;
      }
      return true;
    }
    bool u_read(string& data, struct sockaddr_in& addr) {
      char buf[1024] = {0};
      socklen_t len = sizeof(addr);
      int ret = recvfrom(_sockfd, buf, 1024, 0, (struct sockaddr*)&addr, &len);
      if (ret < 0) {
        return false;
      }
      data.assign(buf, ret);
      return true;
    }
    bool u_send(const string& data, struct sockaddr_in& addr) {
      socklen_t len = sizeof(addr);
      int ret = sendto(_sockfd, &data[0], data.size(), 0, (struct sockaddr*)&addr, len);
      if (ret < 0) {
        return false;
      }
      return true;
    }
  private:
    int _sockfd;
};
