#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#include "../tcpsocket.h"

/*
 * 通过splice实现高效的回射服务器:
 * 1. splice是零拷贝技术, 在内核中实现socket与管道之间的数据拷贝
 * */

int main(int argc, char*argv[]) {
  if (argc != 3) {
    return -1;
  }
  const char* ip = argv[1];
  unsigned short port = atoi(argv[2]);
  int listen_fd = t_socket();
  t_bind(listen_fd, ip, port);
  t_listen(listen_fd, 5);
  while (1) {
    int connfd = t_accept(listen_fd);
    if (connfd < 0) {
      break;
    } else {
      int pipefd[2];
      int ret = pipe(pipefd);
      assert(ret != -1);
      ret = splice(connfd, nullptr, pipefd[1], nullptr, 1024, SPLICE_F_MORE);
      assert(ret != -1);
      ret = splice(pipefd[0], nullptr, connfd, nullptr, 1024, SPLICE_F_MORE);
      assert(ret != -1);
      close(connfd);
    }
  }
  close(listen_fd);
  return 0;
}
