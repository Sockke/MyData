#include "chatService.hpp"
#include "common.hpp"

#include <muduo/base/Logging.h>
using namespace muduo;

ChatService* ChatService::instance() {
    static ChatService chatService;
    return &chatService;
}

ChatService::ChatService() {
    // 业务的注册
    _serviceMap[LOGIN] = std::bind(&ChatService::login, this, _1, _2, _3);
    _serviceMap[REG] = std::bind(&ChatService::reg, this, _1, _2, _3);
    _serviceMap[LOGOUT] = std::bind(&ChatService::logout, this, _1, _2, _3);
    _serviceMap[ONE_CHAT] = std::bind(&ChatService::oneChat, this, _1, _2, _3);
    _serviceMap[ADD_FRIEND] = std::bind(&ChatService::addFriend, this, _1, _2, _3);
    _serviceMap[REMOVE_FRIEND] = std::bind(&ChatService::removeFriend, this, _1, _2, _3);
    _serviceMap[CREATE_GROUP] = std::bind(&ChatService::createGroup, this, _1, _2, _3);
    _serviceMap[ADD_GROUPUSER] = std::bind(&ChatService::addGroupUser, this, _1, _2, _3);
    _serviceMap[REMOVE_GROUPUSER] = std::bind(&ChatService::removeGroupUser, this, _1, _2, _3);
    _serviceMap[GROUP_CHAT] = std::bind(&ChatService::groupChat, this, _1, _2, _3);

    // 连接redis-server, 并注册消息回调
    if (_redis.connect()) {
        _redis.init_notify_handler(std::bind(&ChatService::redisMessageHandler, this, _1, _2));
    }
}

// 业务的分发
void ChatService::serviceHandler(int msgid, const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    if (_serviceMap.find(msgid) == _serviceMap.end()) {
        LOG_ERROR << "no handler with msgid:" << msgid;
        return;
    }
    _serviceMap[msgid](conn, js, timestamp);
}

// 客户端主动退出
void ChatService::clientQuit(const TcpConnectionPtr& conn) {
    User user;

    {
        // 查询该连接
        std::lock_guard<std::mutex> lg(_connMtx);
        for (auto it = _connectionMap.begin(); it != _connectionMap.end(); ++it) {
            if (it->second == conn) {
                // 移除该连接
                user.setId(it->first);
                _connectionMap.erase(it);
                break;
            }
        }
    }

    // 取消订阅channel
    _redis.unsubscribe(user.getId());
    
    if (user.getId() != -1) {
        // 更新该用户的状态
        user.setState("offline");
        _userModel.updateState(user);
    }
}

void ChatService::reset() {
    _userModel.resetState();
}

// 登陆业务
void ChatService::login(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    // 解析js消息对象
    User user;
    int id = js["id"];
    std::string passwd = js["passwd"];
    user.setId(id);

    // 组织响应消息
    json ack_js;
    ack_js["msgid"] = LOGIN_ACK;

    // 登陆
    if (_userModel.find(user) && user.getPasswd() == passwd) {
        // 登陆成功 --- 用户存在并且密码正确
        // 判断是否已经在线
        if (user.getState() == "online") {
            ack_js["errno"] = REPEAT_LOGIN;
            ack_js["errmsg"] = "user is already online";
            std::string ack_string = ack_js.dump();
            int len = ack_string.size();
            ack_string = std::to_string(len) + " " + ack_string;
            conn->send(ack_string);
        } else {
            // 更新登陆状态
            user.setState("online");
            if (_userModel.updateState(user)) {

                // 注册该用户的连接, 考虑线程安全
                {
                    std::lock_guard<std::mutex> lg(_connMtx);
                    _connectionMap.insert({id, conn});
                }

                // 获取好友列表
                std::vector<User> friends;
                if (_friendModel.find(id, friends)) {
                    if (!friends.empty()) {
                        std::vector<std::string> friendsInfo;
                        for (User& user : friends) {
                            json user_js;
                            user_js["id"] = user.getId();
                            user_js["name"] = user.getName();
                            user_js["state"] = user.getState();
                            friendsInfo.push_back(user_js.dump());
                        }
                        ack_js["friends"] = friendsInfo;
                    }
                } else {
                    ack_js["errno"] = FAILED;
                    ack_js["errmsg"] = "find friends list failed";
                    std::string ack_string = ack_js.dump();
                    int len = ack_string.size();
                    ack_string = std::to_string(len) + " " + ack_string;
                    conn->send(ack_string);
                    return;
                }

                // 查询是否有离线消息
                std::vector<std::string> msgs;
                if (_offlineMsgModel.find(id, msgs)) {
                    if (!msgs.empty()) {
                        ack_js["offlineMsg"] = msgs;
                        // 删除离线消息
                        if (!_offlineMsgModel.remove(id)) {
                            ack_js["errno"] = FAILED;
                            ack_js["errmsg"] = "offline remove failed";
                            std::string ack_string = ack_js.dump();
                            int len = ack_string.size();
                            ack_string = std::to_string(len) + " " + ack_string;
                            conn->send(ack_string);
                            return;
                        }
                    }
                } else {
                    // 离线消息查询
                    ack_js["errno"] = FAILED;
                    ack_js["errmsg"] = "offline find failed";
                    std::string ack_string = ack_js.dump();
                    int len = ack_string.size();
                    ack_string = std::to_string(len) + " " + ack_string;
                    conn->send(ack_string);
                    return;
                }
                
                // 查询群组消息
                std::vector<Group> groups;
                if (_groupModel.findGroups(id, groups)) {
                    if (!groups.empty()) {
                        std::vector<std::string> groupsInfo;
                        for (auto& group : groups) {
                            json g_js;
                            g_js["id"] = group.getId();
                            g_js["name"] = group.getName();
                            g_js["info"] = group.getInfo();
                            std::vector<GroupUser> gusers;
                            group.getUsers(gusers);
                            std::vector<std::string> gusersInfo;
                            for (auto& guser : gusers) {
                                json gu_js;
                                gu_js["id"] = guser.getId();
                                gu_js["name"] = guser.getName();
                                gu_js["state"] = guser.getState();
                                gu_js["grouprole"] = guser.getGroupRole();

                                gusersInfo.push_back(gu_js.dump());
                            }
                            g_js["groupusers"] = gusersInfo;

                            groupsInfo.push_back(g_js.dump());
                        }
                        ack_js["groups"] = groupsInfo;
                    }
                } else {
                    ack_js["errno"] = FAILED;
                    ack_js["errmsg"] = "find groups failed";
                    std::string ack_string = ack_js.dump();
                    int len = ack_string.size();
                    ack_string = std::to_string(len) + " " + ack_string;
                    conn->send(ack_string);
                    return;
                }

                // 订阅channel
                _redis.subscribe(id);
                
                ack_js["errno"] = SUCCESS;
                ack_js["id"] = user.getId();
                ack_js["name"] = user.getName();
                ack_js["state"] = user.getState();

                std::string ack_string = ack_js.dump();
                int len = ack_string.size();
                ack_string = std::to_string(len) + " " + ack_string;
                conn->send(ack_string);                
            } else {
                ack_js["errno"] = FAILED;
                ack_js["errmsg"] = "update user state failed";
                std::string ack_string = ack_js.dump();
                int len = ack_string.size();
                ack_string = std::to_string(len) + " " + ack_string;
                conn->send(ack_string); 
            }
        }
    } else {
        // 登陆失败 --- 密码错了或者用户根本不存在
        // 密码错误
        if (user.getId() != -1) {
            ack_js["errno"] = WRONG_PWD;
            ack_js["errmsg"] = "password is wrong";
            std::string ack_string = ack_js.dump();
            int len = ack_string.size();
            ack_string = std::to_string(len) + " " + ack_string;
            conn->send(ack_string);
        } else {
            ack_js["errno"] = FAILED;
            ack_js["errmsg"] = "user is not exist";
            std::string ack_string = ack_js.dump();
            int len = ack_string.size();
            ack_string = std::to_string(len) + " " + ack_string;
            conn->send(ack_string);
        }
    }
}

// 注册业务
void ChatService::reg(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    // 解析js消息对象
    User user;
    user.setName(js["name"].get<string>());
    user.setPasswd(js["passwd"].get<string>());

    // 组织响应消息
    json ack_js;
    ack_js["msgid"] = REG_ACK;

    // 注册
    if (_userModel.insert(user)) {
        // 注册成功
        ack_js["errno"] = SUCCESS;
        ack_js["id"] = user.getId();
        ack_js["name"] = user.getName();

        std::string ack_string = ack_js.dump();
        int len = ack_string.size();
        ack_string = std::to_string(len) + " " + ack_string;
        conn->send(ack_string);
    } else {
        // 注册失败
        ack_js["errno"] = FAILED;
        ack_js["errmsg"] = "user reg failed";

        std::string ack_string = ack_js.dump();
        int len = ack_string.size();
        ack_string = std::to_string(len) + " " + ack_string;
        conn->send(ack_string);
    }
}

// 注销业务
void ChatService::logout(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int userid = js["id"].get<int>();

    {
        // 查询该连接
        std::lock_guard<std::mutex> lg(_connMtx);
        auto it = _connectionMap.find(userid);
        if (it != _connectionMap.end()) {
            _connectionMap.erase(it);
        }
    }

    // 取消订阅channel
    _redis.unsubscribe(userid);

    // 更新该用户的状态
    User user(userid, "", "", "offline");
    _userModel.updateState(user);
}

// 单聊
void ChatService::oneChat(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int toid = js["toid"];

    {
        std::lock_guard<std::mutex> lg(_connMtx);
        auto it = _connectionMap.find(toid);
        if (it != _connectionMap.end()) {
            // 转发消息
            std::string js_string = js.dump();
            int len = js_string.size();
            js_string = std::to_string(len) + " " + js_string;
            it->second->send(js_string);
            return;            
        }    
    }

    User user(toid);
    _userModel.find(user);
    if (user.getState() == "online") {
        // 用户在线, 但是连接在另一台业务服务器上
        std::string js_string = js.dump();
        int len = js_string.size();
        js_string = std::to_string(len) + " " + js_string;
        _redis.publish(toid, js_string);
    } else {
        // 存储离线消息    
        _offlineMsgModel.insert(toid, js.dump());
    } 
}

// 添加好友
void ChatService::addFriend(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int userid = js["id"];
    int friendid = js["friendid"];

    json ack_js;
    ack_js["msgid"] = ADD_FRIEND_ACK;
    User friend_user;
    if (_friendModel.insert(userid, friendid, friend_user)) {
        ack_js["errno"] = SUCCESS;
        ack_js["friend_id"] = friendid;
        ack_js["friend_name"] = friend_user.getName();
        ack_js["friend_state"] = friend_user.getState();
    } else {
        ack_js["errno"] = FAILED;
        ack_js["errmsg"] = "add friend failed";
    }
    std::string ack_string = ack_js.dump();
    int len = ack_string.size();
    ack_string = std::to_string(len) + " " + ack_string;
    conn->send(ack_string);
}

// 删除好友
void ChatService::removeFriend(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int userid = js["id"];
    int friendid = js["friendid"];

    json ack_js;
    ack_js["msgid"] = REMOVE_FRIEND_ACK;
    if (_friendModel.remove(userid, friendid)) {
        ack_js["errno"] = SUCCESS;
        ack_js["friendid"] = friendid;
    } else {
        ack_js["errno"] = FAILED;
        ack_js["errmsg"] = "remove friend failed";
    }
    std::string ack_string = ack_js.dump();
    int len = ack_string.size();
    ack_string = std::to_string(len) + " " + ack_string;
    conn->send(ack_string);
}

// 创建群组
void ChatService::createGroup(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int userid = js["userid"];
    std::string groupname = js["name"];
    std::string groupinfo = js["info"];
    Group group(-1, groupname, groupinfo);

    json ack_js;
    ack_js["msgid"] = CREATE_GROUP_ACK;

    if (_groupModel.create(group)) {
        if (_groupModel.insert(userid, group.getId(), group, "manager")) {
            ack_js["errno"] = SUCCESS;
            ack_js["gid"] = group.getId();
            ack_js["gname"] = group.getName();
            ack_js["ginfo"] = group.getInfo();
            
            std::string ack_string = ack_js.dump();
            int len = ack_string.size();
            ack_string = std::to_string(len) + " " + ack_string;
            conn->send(ack_string);
        } else {
            ack_js["errno"] = FAILED;
            ack_js["errmsg"] = "groupuser add failed";

            std::string ack_string = ack_js.dump();
            int len = ack_string.size();
            ack_string = std::to_string(len) + " " + ack_string;
            conn->send(ack_string);
        }        
    } else {
        ack_js["errno"] = FAILED;
        ack_js["errmsg"] = "group create failed";

        std::string ack_string = ack_js.dump();
        int len = ack_string.size();
        ack_string = std::to_string(len) + " " + ack_string;
        conn->send(ack_string);
    }
}
// 添加群友
void ChatService::addGroupUser(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int userid = js["userid"];
    int groupid = js["groupid"];

    json ack_js;
    ack_js["msgid"] = ADD_GROUPUSER_ACK;
    Group group(groupid);
    if (_groupModel.insert(userid, groupid, group)) {
        json group_js;
        group_js["gid"] = group.getId();
        group_js["gname"] = group.getName();
        group_js["info"] = group.getInfo();
        ack_js["group"] = group_js.dump();

        std::vector<GroupUser> gusers;
        if (_groupModel.findGroupUsersInfo(groupid, gusers)) {
            if (!gusers.empty()) {
                ack_js["errno"] = SUCCESS;
                ack_js["gid"] = groupid;
                std::vector<std::string> gusers_str;
                for (auto& guser : gusers) {
                    json guser_js;
                    guser_js["id"] = guser.getId();
                    guser_js["name"] = guser.getName();
                    guser_js["state"] = guser.getState();
                    guser_js["grouprole"] = guser.getGroupRole();
                    gusers_str.push_back(guser_js.dump());
                }
                ack_js["groupusers"] = gusers_str;

                std::string ack_string = ack_js.dump();
                int len = ack_string.size();
                ack_string = std::to_string(len) + " " + ack_string;
                conn->send(ack_string);
            }
        } else {
            ack_js["errno"] = FAILED;
            ack_js["errmsg"] = "groupuser find failed";

            std::string ack_string = ack_js.dump();
            int len = ack_string.size();
            ack_string = std::to_string(len) + " " + ack_string;
            conn->send(ack_string);
        }
    } else {
        ack_js["errno"] = FAILED;
        ack_js["errmsg"] = "groupuser add failed, maybe group is not exist or you have been in this group";

        std::string ack_string = ack_js.dump();
        int len = ack_string.size();
        ack_string = std::to_string(len) + " " + ack_string;
        conn->send(ack_string);
    }
}
// 删除群友
void ChatService::removeGroupUser(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int userid = js["userid"];
    int groupid = js["groupid"];

    json ack_js;
    ack_js["msgid"] = REMOVE_GROUPUSER_ACK;
    if (_groupModel.remove(userid, groupid)) {
        ack_js["errno"] = SUCCESS;

        std::string ack_string = ack_js.dump();
        int len = ack_string.size();
        ack_string = std::to_string(len) + " " + ack_string;
        conn->send(ack_string);
    } else {
        ack_js["errno"] = FAILED;
        ack_js["errmsg"] = "groupuser remove failed";

        std::string ack_string = ack_js.dump();
        int len = ack_string.size();
        ack_string = std::to_string(len) + " " + ack_string;
        conn->send(ack_string);
    }
}

// 发送群消息
void ChatService::groupChat(const TcpConnectionPtr& conn, json& js, Timestamp timestamp) {
    int id = js["fromid"];
    int groupid = js["groupid"];
    std::string msg = js["msg"];

    std::vector<int> userids;
    if (_groupModel.findGroupUsers(id, groupid, userids)) {
        std::lock_guard<std::mutex> lg(_connMtx);
        for (int& userid : userids) {
            auto it = _connectionMap.find(userid);
            if (it != _connectionMap.end()) {
                // 群友在线, 转发消息
                std::string ack_string = js.dump();
                int len = ack_string.size();
                ack_string = std::to_string(len) + " " + ack_string;
                it->second->send(ack_string);
            } else {
                User user(userid);
                _userModel.find(user);
                if (user.getState() == "online") {
                    // 群友在线, 但是连接在另一台业务服务器上
                    std::string js_string = js.dump();
                    int len = js_string.size();
                    js_string = std::to_string(len) + " " + js_string;
                    _redis.publish(userid, js_string);
                } else {
                    // 群友离线, 存储离线消息
                    _offlineMsgModel.insert(userid, js.dump());
                }
            }
        }
    } else {
        js["errno"] = FAILED;
        js["errmsg"] = "group msg send failed";

        std::string ack_string = js.dump();
        int len = ack_string.size();
        ack_string = std::to_string(len) + " " + ack_string;
        conn->send(ack_string);
    }
}

void ChatService::redisMessageHandler(int userid, const std::string& msg) {
    auto it = _connectionMap.find(userid);
    if (it != _connectionMap.end()) {
        // 转发给在线用户所在的业务服务器
        it->second->send(msg);
    } else {
        // 存储离线消息
        _offlineMsgModel.insert(userid, msg);
    }
}