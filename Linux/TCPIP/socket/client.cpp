#include "tcpsocket.h"
#include "udpsocket.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "ip port..." << endl;
    return -1;
  }
  string ip = argv[1];
  unsigned short port = atoi(argv[2]);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip.c_str());
  addr.sin_port = htons(port);

  UdpSocket csock; 
  csock.u_socket();
  string data;
  cout << "client:";
  cin >> data;
  if (!csock.u_send(data, addr)) {
    cout << "sendto error" << endl;
    return -1;
  }
  data.clear();
  if (!csock.u_read(data, addr)) {
    cout << "readfrom error" << endl;
    return -1;
  }
  cout << "server:" << data << endl;

  return 0;
}

#if 0
int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "ip port..." << endl;
    return -1;
  }
  string ip = argv[1];
  unsigned short port = atoi(argv[2]);
  TcpSocket csock;
  if (!csock.t_socket()) {
    cout << "socket error" << endl;
  }
  if (!csock.t_connect(ip, port)) {
    cout << "connect error" << endl;
  }
  while (1) {
    string data;
    cout << "client:";
    cin >> data;
    if (csock.t_send(data) == false) {
      cout << "send error" << endl;
      break;
    }
    if (csock.t_read(data) == false) {
      cout << "recv error" << endl;
      break;
    }
    cout << "client:" << data << endl;
  }
  csock.t_close();
  return 0;
}
#endif
