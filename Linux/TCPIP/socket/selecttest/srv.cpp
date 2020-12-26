#include <iostream>
#include <cstring>
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>

/*
 * socket上接收到不同的数据, 会触发不同的就绪状态
 * 当socket接收到普通数据时, 会触发可读状态
 * 当socket结束到带外数据时, 会触发异常状态
 * */

int main(int argc, char* argv[]) {
  if (argc < 3) {
    perror("format: ./main ip port");
    return -1;
  }
  const char* ip = argv[1];
  unsigned short port = atoi(argv[2]);
  
  int ret = 0;
  // socket
  int listenfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(listenfd >= 0);
  // bind
  struct sockaddr_in addr;  
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
  ret = bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
  assert(ret != -1);
  // listen
  ret = listen(listenfd, 5);
  assert(ret != -1);
  // accept
  struct sockaddr_in conn_addr;
  socklen_t conn_addr_len = sizeof(conn_addr);
  int connfd = accept(listenfd, (struct sockaddr*)&conn_addr, &conn_addr_len);
  if (connfd < 0) {
    printf("accept error: %d", errno);
    close(listenfd);
  } else {
    char buf[1024];
    // 定义事件集合 
    fd_set read_fds;
    fd_set exception_fds;
    // 初始化事件集合
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);
    while (1) {
      memset(buf, 0x00, 1024);
      // 向事件集合中添加事件(描述符)
      FD_SET(connfd, &read_fds);
      FD_SET(connfd, &exception_fds);
      // select 轮询监控事件集合
      ret = select(connfd + 1, &read_fds, nullptr, &exception_fds, nullptr);
      if (ret < 0) {
        perror("select error");
        break;
      }
      if (FD_ISSET(connfd, &exception_fds)) {
        // 异常事件
        ret = recv(connfd, buf, sizeof(buf)-1, MSG_OOB);
        if (ret <= 0) {
          break;
        }
        printf("get %d bytes urgent data:%s\n", ret, buf);
      }
      // 可读事件
      else if (FD_ISSET(connfd, &read_fds)) {
        ret = recv(connfd, buf, sizeof(buf)-1, 0);
        if (ret <= 0) {
          break;
        }
        printf("get %d bytes normal data:%s\n", ret, buf);
      } 
    }
    close(connfd);
    close(listenfd);
  }
  return 0;
}
