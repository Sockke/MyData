#include "chatServer.hpp"
#include <functional>
#include <string>

#include "json.hpp"
using json = nlohmann::json;

#include "chatService.hpp"

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &addr,
                       const string &name)
    : _server(loop, addr, name), _loop(loop)
{
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    _server.setThreadNum(4);
}

void ChatServer::start() {
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr& conn) {
    if (conn->connected()) {
    } else {
        ChatService::instance()->clientQuit(conn);
        conn->shutdown();
    }
}

void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp timestamp) {
    std::string msg = buf->retrieveAllAsString();
    while (!msg.empty()) {
        size_t pos = msg.find(' ');
        std::string msg_len_str = msg.substr(0, pos);
        int msg_len = atoi(msg_len_str.c_str());
        std::string cur_msg = msg.substr(pos+1, msg_len);

        // 对网络数据进行反序列化
        json js = json::parse(cur_msg);
        // 直接通过msgid来调用业务处理回调即可, 实现了网络模块与业务模块的解耦
        int msgid = js["msgid"].get<int>();
        // msgid -> handler(conn, msg, timestamp)
        ChatService::instance()->serviceHandler(msgid, conn, js, timestamp);

        msg = msg.substr(msg_len_str.size() + 1 + msg_len);
    }
}
