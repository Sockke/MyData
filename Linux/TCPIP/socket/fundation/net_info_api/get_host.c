#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

/*
 * 获取主机信息
 * 1. 通过主机名来获取: gethostbyname(const char* name)
 * 2. 通过ip来获取: gethostbyaddr(const void* addr, size_t len, int type)
 * gethostbyaddr("127.0.0.1", strlen(ip), AF_INET)
 *
 * 默认先从本机/etc/hosts文件中查找, 如果没有会请求DNS
 *
 * */

void getHostInfoByName(const char* name) {
  struct hostent* host_info = gethostbyname(name);
  if (host_info != NULL) {
    const char* host_name = host_info->h_name;
    char** host_aliases = host_info->h_aliases;
    int address_len = host_info->h_length;
    // 网络字节序地址列表, struct in_addr 类型
    char** host_addr_list = host_info->h_addr_list;

    printf("host name: %s\n", host_name);

    printf("host aliases:\n");
    char** host_alias = host_aliases;
    int i = 0;
    while (*host_alias != NULL && strlen(*host_alias)) {
      printf("%d: %s\n", i, *host_alias);
      ++i;
      ++host_alias;
    }

    printf("address len: %d\n", address_len);

    printf("host address:\n");
    char** host_addr = host_addr_list; 
    i = 0;
    while (*host_addr != NULL && strlen(*host_addr)) {
      struct in_addr inaddr = *(struct in_addr*)(*host_addr);
      printf("%d: %s\n", i, inet_ntoa(inaddr));
      ++i;
      ++host_addr;
    }
  } else {
    printf("no info about %s\n", name);
  }
}

int main() {
  const char* name = "localhost";
  getHostInfoByName(name);
  
  return 0;
}
