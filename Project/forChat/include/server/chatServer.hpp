#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <iostream>
#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"

using std::cout;
using std::endl;

using namespace muduo;
using namespace muduo::net;

class ChatServer {
public:
    ChatServer(EventLoop *loop,
               const InetAddress &addr,
               const string &name);

    void start();
    
private:
   void onConnection(const TcpConnectionPtr&);
   void onMessage(const TcpConnectionPtr&, Buffer*, Timestamp);

   TcpServer _server;
   EventLoop *_loop;
};

#endif
