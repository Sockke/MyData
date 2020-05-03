#include "tcpsocket.hpp"
#include <cassert>
#include <fcntl.h>
#include <string>
#include <cstring>

// 创建socket
int tsocket() {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(fd != -1);
    return fd;
}

// 连接
void tconnect(int fd, const char* ip, unsigned short port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip); // 转换成点分十进制
    addr.sin_port = htons(port);

    socklen_t len = sizeof(addr);

    int ret = connect(fd, (sockaddr*)&addr, len);
    assert(ret != -1);
}

// 发送消息
int tsend(int fd, const char* msg) {
    size_t has_send = 0;
    size_t len = strlen(msg);
    while (has_send < len) {
        int ret = send(fd, msg + has_send, len - has_send, 0);
        if (ret < 0) {
            if (errno == EAGAIN) {
                continue;
            } else {
                return -1;
            }
        } else {
            has_send += ret;
        }
    }
    return len;
}

// 接收消息
int trecv_peek(int fd) {
    std::string msg(4096, 0);
    int ret = recv(fd, &msg[0], 4095, MSG_PEEK);
    if (ret < 0) {
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            usleep(3000);
            return 0;
        } else {
            return -1;
        }
    } else {
        int pos = msg.find(' ');
        msg = msg.substr(0, pos);
        return msg.size() + 1 + atoi(msg.c_str());
    }
}
std::string trecv_peek(int fd, int len) {
    std::string msg(len, 0);
    int ret = recv(fd, &msg[0], len, MSG_PEEK);
    if (ret < 0) {
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            usleep(3000);
            return "";
        } else {
            return "";
        }
    } else {
        int pos = msg.find(' ');
        return msg.substr(pos+1);
    }
}
int trecv(int fd, std::string& msg, int len) {
    msg.resize(len, 0);
    size_t has_recv = 0;
    while (has_recv < len) {
        int ret = recv(fd, &msg[has_recv], len - has_recv, 0);
        if (ret < 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                usleep(3000);
                continue;
            } else {
                return -1;
            }
        } else if (ret == 0) {
            perror("peer shutdown");
            return 0;
        } else {
            has_recv += ret;
        }
    }
    return len;
}

// 设置非阻塞
void setnonblock(int fd) {
    int flag = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

