#include "tcp.h"

int main() {
  const char* ip = "192.168.163.99";
  unsigned short port = 9000;
  TcpSocket cli;
  cli.t_socket(); 
  cli.t_connect(ip, port);
  while (1) {
    string data;
    cout << "cli send:";
    cin >> data;
    cli.t_send(data);
  }
  return 0;
}
