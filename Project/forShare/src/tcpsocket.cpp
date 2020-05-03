#include "../include/tcpsocket.h"

//#define Log(format,...) fprintf(stdout, format, ##__VA_ARGS__)
    

TcpSocket::TcpSocket() 
  : _sockfd(-1)
{}

TcpSocket::~TcpSocket() {}

void TcpSocket::tsocket() {
  _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (_sockfd < 0) {
    perror("sock error");
    exit(-1);
  }
  // 设置套接字选项实现地址重用, 解决服务端主动关闭进入TIME_WAIT,     
  // 其端口短时间内不能被重用的问题    
  int opt = 1;    
  setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(int));
}

void TcpSocket::tbind(const std::string& sip, short sport) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET; 
  addr.sin_addr.s_addr = inet_addr(sip.c_str());
  addr.sin_port = htons(sport);
  socklen_t len = sizeof(struct sockaddr_in);
  int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
  if (ret < 0) {
    perror("bind error");
    exit(-1);
  }
}

void TcpSocket::tlisten(int maxconnect) {
  int ret = listen(_sockfd, maxconnect);
  if (ret < 0) {
    perror("listen error");
    exit(-1);
  }
}

int TcpSocket::getSockfd() const {
  return _sockfd;
}

void TcpSocket::setSockfd(int new_sockfd) {
  _sockfd = new_sockfd;
}

void TcpSocket::setNonBlock() {
  int flag = fcntl(_sockfd, F_GETFL, 0);    
  fcntl(_sockfd, F_SETFL, O_NONBLOCK | flag);    
}

bool TcpSocket::taccept(TcpSocket& csock) {
  struct sockaddr_in caddr;
  socklen_t len = sizeof(struct sockaddr_in);
  int new_sockfd = accept(_sockfd, (struct sockaddr*)&caddr, &len);
  if (new_sockfd < 0) {
    return false;
  }
  csock.setSockfd(new_sockfd);
  csock.setNonBlock();
  return true;
}

bool TcpSocket::trecvPeek(std::string& data) {
  char buf[MAX_HEAD] = {0};
  int ret = recv(_sockfd, buf, MAX_HEAD - 1, MSG_PEEK);
  if (ret < 0) {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
      return true;
    } else {
      perror("recv with peek error");
      return false;
    }
  } else if (ret == 0) {
    perror("peer shutdown");
    return true;
  }
  data.assign(buf, ret);
  return true;
}

bool TcpSocket::trecv(std::string& data, size_t len) {
  data.resize(len);
  size_t has_recv = 0;
  while (has_recv < len) {
    int ret = recv(_sockfd, &data[0] + has_recv, len - has_recv, 0);
    if (ret < 0) {
      if (errno == EAGAIN) {
        usleep(3000);
        continue;
      }
      perror("recv error");
      return false;
    } else if (ret == 0) {
      perror("peer shutdown");
      return false;
    } else {
      has_recv += ret;
    }
  }
  return true;
}

bool TcpSocket::tsend(const std::string& data) {
  size_t has_send = 0;
  size_t len = data.size();
  while (has_send < len) {
    int ret = send(_sockfd, &data[has_send], data.size() - has_send, 0);
    if (ret < 0) {
      if (errno == EAGAIN) {
        continue;
      }
      perror("send error");
      return false;
    } else {
      has_send += ret;
    }
  }
  return true;
}
