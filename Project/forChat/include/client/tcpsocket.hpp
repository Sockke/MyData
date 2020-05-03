#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// 创建套接字
int tsocket();
// 连接
void tconnect(int fd, const char* ip, unsigned short port);
// 发送消息
int tsend(int fd, const char* msg);
// 接收消息
int trecv_peek(int fd);
std::string trecv_peek(int fd, int len);
int trecv(int fd, std::string& msg, int len);

// 设置非阻塞
void setnonblock(int fd);

#endif