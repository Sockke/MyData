#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "../tcpsocket.h"

/*
 * web服务器中的集中写和集中读
 * 1. 分散读, readv
 * 2. 集中写, writev, 在web服务器中, 在组织http响应时, 一般响应头信息和正文信息是放在不同的内存中的.
 * 我们不需要将两者拼接到一块再发送, 而是通过iovec这个结构体来组织两块内存, 通过writev实现集中写
 *
 *
 * 优势:
 * 减少系统调用的开销, 读写非连续内存, 如果使用read需要分多次调用.
 * */

#define BUF_SIZE 1024

const char* stat_lines[] = {
  "200 OK", 
  "500 Internal server error"
};

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
    printf("accept errno: %d\n", c_sock);
  } else {
    // 存储http响应头
    char header_buf[BUF_SIZE];
    memset(header_buf, '\0', BUF_SIZE);
    // 存储正文信息
    char* file_buf = NULL;

    struct stat file_stat; 
    const char* filename = argv[3];
    // 文件是否有效
    bool valid = true;  
    if (stat(filename, &file_stat) < 0) {
      // 文件不存在
      valid = false;
    } else {
      if (S_ISDIR(file_stat.st_mode)) {
        // 文件是一个目录
        valid = false;
      } else if (file_stat.st_mode & S_IROTH) {
        // 有读权限  
        int fd = open(filename, O_RDONLY);
        assert(fd >= 0);
        file_buf = new char[file_stat.st_size + 1];
        memset(file_buf, '\0', file_stat.st_size + 1);
        if (read(fd, file_buf, file_stat.st_size) < 0) {
          // 文件读取失败
          valid = false;
        }
      } else {
        // 没有读权限
        valid = false; 
      }

      // header_buf中数据长度
      int len = 0; 
      int ret = 0;
      if (valid) {
        // 读取文件成功, 正常应答
        ret = snprintf(header_buf, BUF_SIZE - 1, "%s %s\r\n",
            "HTTP/1.1", stat_lines[0]);
        len += ret;
        ret = snprintf(header_buf + len, BUF_SIZE - 1 - len, "Content-Length: %lu\r\n",
            file_stat.st_size);
        len += ret;
        ret = snprintf(header_buf + len, BUF_SIZE - 1 - len, "\r\n");
        len += ret;

        // 集中写
        struct iovec iov[2];
        iov[0].iov_base = header_buf;
        iov[0].iov_len = len;
        iov[1].iov_base = file_buf;
        iov[1].iov_len = file_stat.st_size;
        writev(c_sock, iov, 2);
      } else {
        // 读取文件失败
        ret = snprintf(header_buf, BUF_SIZE - 1, "%s %s\r\n", 
            "HTTP/1.1", stat_lines[1]);
        len += ret;
        ret = snprintf(header_buf + len, BUF_SIZE - 1 - len, "\r\n");

        send(c_sock, header_buf, strlen(header_buf), 0);
      }
    }
    close(c_sock);
  }

  return 0;
}
