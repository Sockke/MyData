#include "../include/server.h"

int main() {
  Server srv("192.168.163.99", 9000);
  srv.reg();
  srv.listen();
  return 0;
}
