#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "../tcpsocket.h"

/*
 *
 *
 * 服务器通过listen监听新连接的到来, 当新连接到来时会放到一个连接队列中,
 * 当服务端通过except从连接队列中将新连接取出, 进行通信
 * 在服务端except之前, 连接队列中的连接如果断开连接, 服务端是不会将它移除的,
 * 通过except依然会拿到这个已经关闭的连接
 * */


int main(int argc, char* argv[]) {
  if (argc != 3) {
    perror("format requirement: ./server ip port");
    return 1;
  }

  const char* ip = argv[1];
  unsigned short port = atoi(argv[2]);

  int l_sock = t_socket();
  t_bind(l_sock, ip, port);
  t_listen(l_sock, 5);

  sleep(20);

  int c_sock = t_accept(l_sock);
  if (c_sock < 0) {
    perror("no such connection in connected queue");
  } else {
    struct sockaddr_in c_addr;
    socklen_t len = sizeof(c_addr);
    // 获取该连接对端的地址信息
    getpeername(c_sock, (struct sockaddr*)&c_addr, &len);
    printf("connected with %s: %u\n", inet_ntoa(c_addr.sin_addr), c_addr.sin_port);
    close(c_sock);
  }

  close(l_sock);
  
  return 0;
}
