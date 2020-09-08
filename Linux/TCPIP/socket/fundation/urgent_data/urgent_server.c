#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../tcpsocket.h"


/*
 * 带外数据:
 * 1. 设置recv/send中的socket选项为MSG_OOB来收发带外数据(紧急数据)
 * 2. 由于TCP头部中的紧急指针是指向带外数据的下一个位置, 并且带外数据缓冲区为1字节,
 * 因此最终被当作带外数据的是紧急指针的前继字节数据.
 * 比如说"abc"以OOB的方式进行发送, 接收端通过OOB接收时, 只有'c'才被当作带外数据,
 * 其他都被当作普通数据进行存储
 * 3. 带外数据会截断普通数据的接收, 比如说发送端发送普通数据"123", 再发送带外数据"abc",
 * 最后发送普通数据"123", 接收端不能一次行全部接收, 而是分三次, 第一次接收到"123ab",
 * 第二次接收到"c", 第三次接收到"123"
 *
 *
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

  int c_sock = t_accept(l_sock);
  if (c_sock < 0) {
    perror("no such connection in connected queue");
  } else {
    char buf[BUF_SIZE] = {0};

    int ret = recv(c_sock, buf, BUF_SIZE - 1, 0);
    printf("got %d bytes of data: %s\n", ret, buf);

    memset(buf, '\0', BUF_SIZE);
    ret = recv(c_sock, buf, BUF_SIZE - 1, MSG_OOB);
    printf("got %d bytes of data: %s\n", ret, buf);

    memset(buf, '\0', BUF_SIZE);
    ret = recv(c_sock, buf, BUF_SIZE - 1, 0);
    printf("got %d bytes of data: %s\n", ret, buf);

    close(c_sock);
  }

  close(l_sock);
  
  return 0;
}
