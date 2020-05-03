#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const int MAX_HEAD = 1024;

class TcpSocket {
  public:
    TcpSocket();
    ~TcpSocket();
    void tsocket(); // 创建套接字
    void tbind(const std::string& sip, short sport); // 绑定地址信息
    void tlisten(int maxconnect = 5); // 开始监听
    bool taccept(TcpSocket& csock); // 为连接分配新的套接字与之通信
    int getSockfd() const;
    void setSockfd(int new_sockfd);
    bool trecvPeek(std::string& data);
    bool trecv(std::string& data, size_t len);
    bool tsend(const std::string& data);
  private:
    void setNonBlock();
    int _sockfd;
};
