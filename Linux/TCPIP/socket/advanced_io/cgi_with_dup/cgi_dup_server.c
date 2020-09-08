#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "../tcpsocket.h"


/*
 * 实现一个简单的cgi服务器, 使用dup或dup2将 STDOUT 重定向到 连接socket
 * 本质上就是复制文件描述符表 表项 到另一个描述符表 表项
 *
 * 1. 实现重定向的系统调用
 * int dup(int file_no)
 * 将文件描述符表中引用计数为0的最小文件描述符, 重定向到 file_no
 *
 * int dup(int file_no, int file_no2), 返回不小于file_no2的整数值
 * 将file_no2重定向到file_no, 重定向之前会close(file_no2)
 *
 * */

int main(int argc, char* argv[]) {
  if (argc != 3) {
    perror("format: ./server ip port");
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
    // 关闭 标准输出
    // close(STDOUT_FILENO);
    // 重定向 连接socket, c_sock被重定向到 STDOUT
    // dup(c_sock);
    dup2(c_sock, STDOUT_FILENO);
    
    printf("hello world\n");
  }
  close(c_sock);
}
