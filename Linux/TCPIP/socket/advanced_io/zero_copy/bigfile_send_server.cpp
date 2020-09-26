#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#include "../tcpsocket.h"

/*
 * 通过sendfile, 在网络中实现高效的大文件传输
 * 1. sendfile是零拷贝技术, 在内核中实现socket与本地文件的数据拷贝
 * 不需要用户态与内核态之间的数据拷贝, 大大提高了性能
 *
 * */

int main(int argc, char* argv[]) {
  if (argc != 4) {
    perror("format: ./server ip port filename");
    return 1;
  }
  const char* ip = argv[1];
  unsigned short port = atoi(argv[2]);

  int l_sock = t_socket();
  t_bind(l_sock, ip, port);
  t_listen(l_sock, 5);

  int c_sock = t_accept(l_sock);
  if (c_sock < 0) {
    printf("errno is %d\n", c_sock);
  } else {
    const char* filename = argv[3];
    struct stat file_stat;
    if (stat(filename, &file_stat) < 0)  {
      printf("no such file named %s\n", filename);
    } else {
      int fd = open(filename, O_RDONLY);
      sendfile(c_sock, fd, nullptr, file_stat.st_size);
    }
  }

  close(c_sock);
}
