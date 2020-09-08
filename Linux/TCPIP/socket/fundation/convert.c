#include <stdio.h>
#include <arpa/inet.h>

void ipConvert() {
  // 将点分十进制 转换成 网络字节序整数
  const char* ip1 = "192.168.163.99";
  unsigned int num1 = inet_addr(ip1);
  printf("%s: %u\n", ip1, num1);

  struct in_addr addr1;
  int ret = inet_aton(ip1, &addr1);
  if (ret == 1) {
    printf("%s: %u\n", ip1, addr1.s_addr);
  }


  // 将网络字节序整数 转换成 点分十进制
  // inet_ntoa返回的指针指向一块静态变量, 是一个不可重入的函数
  const char* ip2 = inet_ntoa(addr1);
  struct in_addr addr2;
  addr2.s_addr = addr1.s_addr + 1;
  const char* ip3 = inet_ntoa(addr2);
  printf("%u: %s\n", addr1.s_addr, ip2);
  printf("%u: %s\n", addr2.s_addr, ip3);
}

void portConvert() {
  // 将端口号 转换成 网络字节序整数
  unsigned short port = 80;
  unsigned short n_port = htons(port);
  printf("%u: %u\n", port, n_port);
  // 将网络字节序整数 转换成 端口号
  port = ntohs(n_port);
  printf("%u: %u\n", n_port, port);
}

int main() {
  return 0;
}
