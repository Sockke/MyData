#include <sys/socket.h>
#include <arpa/inet.h>

#include <assert.h>
#include <stdio.h>

#define BUF_SIZE 1024


int t_socket() {
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  assert(sock != -1);
  // 设置地址重用, 即使sock处于TIME_WAIT状态, 与之绑定的地址信息依然可以被立即重用
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  return sock;
}

void t_bind(int fd, const char* ip, unsigned short port) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);
  int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
  assert(ret != -1);
}

void t_listen(int fd, int backlog) {
  int ret = listen(fd, backlog);
  assert(ret != -1);
}

int t_accept(int fd) {
  struct sockaddr_in c_addr;
  socklen_t len = sizeof(c_addr);
  int c_sock = accept(fd, (struct sockaddr*)&c_addr, &len);
  return c_sock;
}

void t_connect(int fd, const char* ip, unsigned short port) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
  assert(ret != -1);
}
