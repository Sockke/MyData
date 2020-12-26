#include <iostream>
#include <cstring>
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    perror("format: ./main ip port");
    return -1;
  }
  const char* ip = argv[1];
  unsigned short port = atoi(argv[2]);
  
  int ret = 0;
  // socket
  int connfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(connfd >= 0);
  // connet
  struct sockaddr_in addr;
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
  ret = connect(connfd, (struct sockaddr*)&addr, sizeof(addr));
  assert(ret != -1);
  
  const char* normal = "123";
  const char* urgent = "a";
  
  //ret = send(connfd, normal, strlen(normal), 0);
  //if (ret < 0) {
  //  perror("send error");
  //}
  ret = send(connfd, urgent, strlen(urgent), MSG_OOB);
  if (ret < 0) {
    perror("send error");
  }
  //sleep(10);
  close(connfd);
  return 0;
}
