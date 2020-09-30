#include <stdio.h>
#include <fcntl.h>

void setnonblocking(int sockfd) {
  int old_flag = fcntl(sockfd, F_GETFL);
  fcntl(sockfd, F_SETFL, old_flag | O_NONBLOCK);
}

int main() {
  return 0;
}
