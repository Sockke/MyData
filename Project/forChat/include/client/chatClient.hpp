#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
using std::cout;
using std::endl;

#include "tcpsocket.hpp"

#include "json.hpp"
using json = nlohmann::json;

#include "common.hpp"

using RESPONSE_HANDLER = std::function<bool(int fd, json& js)>;
using COMMAND_HANDLER = std::function<void(int)>;


class MainService {
public:
    static MainService* instance(); 
    void login(int);
    void reg(int);
    void updateFriendState(int, const std::string&);

    bool serviceAck(int msgid, int fd, json& js);
    void commandService(const std::string& msgid, int fd);
private:
    MainService();

    bool loginAck(int fd, json& js);
    bool regAck(int fd, json& js);
    bool addFriendAck(int fd, json& js);
    bool removeFriendAck(int fd, json& js); 
    bool oneChatAck(int fd, json& js);
    bool createGroupAck(int fd, json& js);
    bool addGroupUserAck(int fd, json& js);
    bool groupChatAck(int fd, json& js);
    std::unordered_map<int, RESPONSE_HANDLER> _responseMap;

    void quit(int); // 退出
    void man(int); // 手册
    void showFriendList(int); // 展示好友列表
    void addFriend(int); // 添加好友
    void removeFriend(int); // 删除好友
    void oneChat(int); // 单聊
    void showGroupList(int); // 展示群组信息
    void createGroup(int); // 创建群组
    void addGroupUser(int); // 添加群友
    void groupChat(int); // 群聊
    std::unordered_map<std::string, COMMAND_HANDLER> _commandMap;
    
};

#endif