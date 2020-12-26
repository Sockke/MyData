#include <stdio.h>
#include <unistd.h>

int main() {
  int uid = getuid();
  int euid = geteuid();
  printf("uid = %d\n", uid);
  printf("euid = %d\n", euid);
  return 0;
}
