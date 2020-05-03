#include "tcpsocket.h"
#include <thread>
#include "udpsocket.h"

int main() {
  string ip = "192.168.163.99";
  unsigned short port = 9000;
  UdpSocket ssock;
  ssock.u_socket();
  ssock.u_bind(ip, port);

  while (1) {
    struct sockaddr_in caddr;
    string data;
    if (!ssock.u_read(data, caddr)) {
      cout << "recvfrom error" << endl;
      return -1;
    }
    cout << "client:" << data << endl;
    ssock.u_send(data, caddr);
  }

  return 0;
}

#if 0
int main() {
  string ip = "192.168.163.99";
  unsigned short port = 9000;
  TcpSocket lsock;
  lsock.t_socket();
  lsock.t_bind(ip, port);
  lsock.t_listen();

  while (1) {
    TcpSocket csock;
    if (!lsock.t_accept(csock)) {
      usleep(1000);
      continue;
    }
    thread thr([&](TcpSocket csock)->void{
        while (1) {
        string data;
        if (csock.t_read(data) == false) {
        cout << "recv error" << endl;
        csock.t_close();
        break;
        }
        cout << "cli:" << data << endl;
        if (csock.t_send(data) == false) {
        cout << "send error" << endl;
        csock.t_close();
        break;
        }
        }
    }, csock);
    thr.detach();
  }
  return 0;
}
#endif
