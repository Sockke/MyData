#include "../tcpsocket.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
  if (argc != 3) {
    perror("format requirement: ./client ip port");
    return 1;
  }

  const char* ip = argv[1];
  unsigned short port = atoi(argv[2]);

  int c_sock = t_socket();
  t_connect(c_sock, ip, port);

  const char* normal_data = "123";
  const char* urgent_data = "abc";
  send(c_sock, normal_data, strlen(normal_data), 0);
  // 发送带外数据(紧急数据)
  send(c_sock, urgent_data, strlen(urgent_data), MSG_OOB);
  send(c_sock, normal_data, strlen(normal_data), 0);

  close(c_sock);

  return 0;
}
