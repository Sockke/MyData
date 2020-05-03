#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <iostream>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <muduo/net/TcpConnection.h>
#include "json.hpp"

using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

#include "chatModel.hpp"
#include "redis.hpp"

/*
业务类
*/

using SERVICE_HANDLER = std::function<void(const TcpConnectionPtr&, json&, Timestamp)>;

// 业务模块设置成单例模式
class ChatService {
public:
    static ChatService* instance();
    // 业务的分发
    void serviceHandler(int msgid, const TcpConnectionPtr&, json&, Timestamp);
    // 客户端主动退出
    void clientQuit(const TcpConnectionPtr&);
    // 在线用户清除
    void reset();
private:
    ChatService();
    ChatService(const ChatService&) = delete;
    ChatService& operator=(const ChatService&) = delete;

    // 登陆业务
    void login(const TcpConnectionPtr&, json&, Timestamp);
    // 注册业务
    void reg(const TcpConnectionPtr&, json&, Timestamp);
    // 注销业务
    void logout(const TcpConnectionPtr&, json&, Timestamp);
    // 一对一聊天
    void oneChat(const TcpConnectionPtr&, json&, Timestamp);
    // 添加好友
    void addFriend(const TcpConnectionPtr&, json&, Timestamp);
    // 删除好友
    void removeFriend(const TcpConnectionPtr&, json&, Timestamp);
    // 创建群组
    void createGroup(const TcpConnectionPtr&, json&, Timestamp);
    // 添加群友
    void addGroupUser(const TcpConnectionPtr&, json&, Timestamp);
    // 删除群友
    void removeGroupUser(const TcpConnectionPtr&, json&, Timestamp);
    // 发送群消息
    void groupChat(const TcpConnectionPtr&, json&, Timestamp);

    // msgid -> handler
    std::unordered_map<int, SERVICE_HANDLER> _serviceMap;
    
    // 用户连接的管理
    std::unordered_map<int, const TcpConnectionPtr&> _connectionMap;
    std::mutex _connMtx; // 动态管理连接的锁
    
    // model对象, 间接操作数据库
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    Redis _redis;
    void redisMessageHandler(int userid, const std::string& msg);
};

#endif