#include <stdio.h>
#include <netdb.h>
#include <assert.h>
#include <string.h>

/*
 * 获取服务信息
 * 1. 通过服务名来获取: getservbyname(const char* name, const char* proto)
 * 2. 通过端口来获取: getservbyport(int port, const char* proto)
 *
 * 去本机/etc/services中查找
 *
 * */

void getServByName(const char* name) {
  assert(name != NULL);
  struct servent* serv_info = getservbyname(name, "tcp");
  if (serv_info != NULL) {
    const char* serv_name = serv_info->s_name;
    char** serv_aliases = serv_info->s_aliases;
    // 网络字节序的 端口号
    unsigned short serv_port = serv_info->s_port;
    const char* serv_proto = serv_info->s_proto;

    printf("service name: %s\n", serv_name);

    printf("service aliases:\n");
    char** serv_alias = serv_aliases;
    int i = 0;
    while (*serv_alias != NULL && strlen(*serv_alias)) {
      printf("%d service alias: %s\n", i, *serv_alias);
      ++i;
      ++serv_alias;
    }

    printf("service port: %d\n", ntohs(serv_port));

    printf("service protocol: %s\n", serv_proto);
  } else {
    printf("no service named %s\n", name);
  }
}

int main() {
  const char* name = "mysql";
  getServByName(name);
  return 0;
}
