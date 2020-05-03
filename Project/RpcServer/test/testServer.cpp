#include "../include/rpcServer.h"
#include "../include/checkUser.h"

int main() {
  RpcServer* server = RpcServer::getInstance();
  server->serviceRegister(new CheckUser());
  server->start();
  return 0;
}
