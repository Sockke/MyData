#include "chatClient.hpp"
#include "tcpsocket.hpp"
#include "menu.hpp"
#include "clientUser.hpp"

#include "common.hpp"
#include <thread>
#include <mutex>
#include <sstream>

const char* ip = "127.0.0.1";
unsigned short port = 8000;

// response
int response(int fd, json& js) {
    while (1) {
        int len = trecv_peek(fd);
        if (len == 0) {
            continue;
        }
        std::string data;
        int ret = trecv(fd, data, len);
        if (ret == 0) {
            close(fd);
            exit(0);
        }
        int pos = data.find(' ');
        data = data.substr(pos + 1);

        js = json::parse(data);
        int msgid = js["msgid"];
        return msgid;
    }
}

// 读线程函数
std::once_flag my_once_flag;
void readFunc(int fd) {
    std::thread thr([=]()->void{
        while (1) {
            int len = trecv_peek(fd);
            if (len == 0) {
                continue;
            }

            std::string data = trecv_peek(fd, len);
            if (!data.empty()) {
                json js = json::parse(data);
                int msgid = js["msgid"];
                if (msgid == LOGIN_ACK || msgid == REG_ACK) {
                    // 对于登陆与注册网络数据的读取交给主线程来做
                    continue;
                }
            }

            data.clear();
            int ret = trecv(fd, data, len);
            if (ret == 0) {
                close(fd);
                exit(0);
            }
            int pos = data.find(' ');
            data = data.substr(pos + 1);

            json js = json::parse(data);
            int msgid = js["msgid"];
            MainService::instance()->serviceAck(msgid, fd, js);
        }
    });
    thr.detach();
}


MainService* MainService::instance() {
    static MainService service;
    return &service;
}
MainService::MainService() {
    _responseMap[LOGIN_ACK] = std::bind(&MainService::loginAck, this, std::placeholders::_1, std::placeholders::_2);
    _responseMap[REG_ACK] = std::bind(&MainService::regAck, this, std::placeholders::_1, std::placeholders::_2);
    _responseMap[ADD_FRIEND_ACK] = std::bind(&MainService::addFriendAck, this, std::placeholders::_1, std::placeholders::_2);
    _responseMap[REMOVE_FRIEND_ACK] = std::bind(&MainService::removeFriendAck, this, std::placeholders::_1, std::placeholders::_2);
    _responseMap[ONE_CHAT] = std::bind(&MainService::oneChatAck, this, std::placeholders::_1, std::placeholders::_2);
    _responseMap[CREATE_GROUP_ACK] = std::bind(&MainService::createGroupAck, this, std::placeholders::_1, std::placeholders::_2);
    _responseMap[ADD_GROUPUSER_ACK] = std::bind(&MainService::addGroupUserAck, this, std::placeholders::_1, std::placeholders::_2);
    _responseMap[GROUP_CHAT] = std::bind(&MainService::groupChatAck, this, std::placeholders::_1, std::placeholders::_2);

    _commandMap[":quit"] = std::bind(&MainService::quit, this, std::placeholders::_1);
    _commandMap[":man"] = std::bind(&MainService::man, this, std::placeholders::_1);
    _commandMap[":show friends"] = std::bind(&MainService::showFriendList, this, std::placeholders::_1);
    _commandMap[":add friend"] = std::bind(&MainService::addFriend, this, std::placeholders::_1);
    _commandMap[":remove friend"] = std::bind(&MainService::removeFriend, this, std::placeholders::_1);
    _commandMap[":one chat"] = std::bind(&MainService::oneChat, this, std::placeholders::_1);
    _commandMap[":show groups"] = std::bind(&MainService::showGroupList, this, std::placeholders::_1);
    _commandMap[":create group"] = std::bind(&MainService::createGroup, this, std::placeholders::_1);
    _commandMap[":add group"] = std::bind(&MainService::addGroupUser, this, std::placeholders::_1);
    _commandMap[":group chat"] = std::bind(&MainService::groupChat, this, std::placeholders::_1);
}
// 登陆
void  MainService::login(int fd) {
    int id = 0;
    std::string passwd;
    cout << "userid:";
    std::cin >> id;
    std::cin.get();
    cout << "password:";
    std::cin >> passwd;
    std::cin.get();

    json js;
    js["msgid"] = LOGIN;
    js["id"] = id;
    js["passwd"] = passwd;
    std::string msg = js.dump();
    msg = std::to_string(msg.size()) + " " + msg;
    tsend(fd, msg.c_str());
}
// 注册
void  MainService::reg(int fd) {
    std::string username;
    std::string passwd;
    cout << "username:";
    std::getline(std::cin, username);
    cout << "password:";
    std::cin >> passwd;

    json js;
    js["msgid"] = REG;
    js["name"] = username;
    js["passwd"] = passwd;

    std::string msg = js.dump();
    msg = std::to_string(msg.size()) + " " + msg;
    tsend(fd, msg.c_str());
}
// 更新好友状态(写扩散)
void MainService::updateFriendState(int fd, const std::string& state) {
    std::vector<User>& friends = ClientUser::instance()->getFriends();
    for (auto& e : friends) {
        if (e.getState() == "online") {
            json js;
            js["msgid"] = ONE_CHAT;
            js["fromid"] = ClientUser::instance()->getId();
            js["toid"] = e.getId();
            js["state"] = state;

            std::string msg = js.dump();
            msg = std::to_string(msg.size()) + " " + msg;
            tsend(fd, msg.c_str());
        }
    }
}
/*
    response message
*/
bool MainService::serviceAck(int msgid, int fd, json& js) {
    if (_responseMap.find(msgid) == _responseMap.end()) {
        return false;
    } else {
        return _responseMap[msgid](fd, js);
    }
}
bool MainService::loginAck(int fd, json& js) {
    int err_no = js["errno"];
    if (err_no == SUCCESS) {
        // 保存用户信息
        int id = js["id"];
        std::string name = js["name"];
        std::string state = js["state"];
        User user(id, name, "", state);
        ClientUser::instance()->setUser(user);
        // 保存好友列表信息, 群组列表信息, 离线消息信息
        if (js.contains("friends")) {
            std::vector<std::string> friends = js["friends"];
            for (auto& e : friends) {
                json f = json::parse(e);
                int fid = f["id"];
                std::string fname = f["name"];
                std::string fstate = f["state"];
                User fuser(fid, fname, "", fstate);
                ClientUser::instance()->addFriend(fuser);
            }
        }
        // 获取离线消息
        if (js.contains("offlineMsg")) {
            std::vector<std::string> offlineMsg = js["offlineMsg"];
            for (auto& e : offlineMsg) {
                json js_offline = json::parse(e);
                int fromid = js_offline["fromid"];
                std::string msg = js_offline["msg"];
                if (js_offline.contains("toid")) {
                    // 单聊离线消息
                    cout << "a message from " << fromid << endl;
                    ClientUser::instance()->addOfflineMsg(fromid, msg);
                } else if (js_offline.contains("groupid")) {
                    // 群聊离线消息cle
                    int groupid = js_offline["groupid"];
                    cout << "a group message from " << groupid << endl;
                    std::stringstream ss;
                    ss << fromid << " say:" << msg;
                    ClientUser::instance()->addGroupOfflineMsg(groupid, ss.str());
                }
            }
        }
        // 获取群组列表信息
        if (js.contains("groups")) {
            std::vector<std::string> groups_str = js["groups"];

            for (auto& group_str : groups_str) {
                json g_json = json::parse(group_str);
                int gid = g_json["id"];
                std::string gname = g_json["name"];
                std::string info = g_json["info"];
                std::vector<std::string> gusers_str = g_json["groupusers"];
                // 群成员
                std::vector<GroupUser> gusers;
                for (auto& user : gusers_str) {
                    json u_json = json::parse(user);
                    int uid = u_json["id"];
                    std::string uname = u_json["name"];
                    std::string ustate = u_json["state"];
                    std::string grouprole = u_json["grouprole"];
                    GroupUser guser(grouprole);
                    guser.setId(uid);
                    guser.setName(uname);
                    guser.setState(ustate);
                    gusers.push_back(guser);
                }
                Group group(gid, gname, info);
                group.setUsers(gusers);

                ClientUser::instance()->addGroup(group);
            }
        }

        // 通知在线好友, 我已上线
        MainService::instance()->updateFriendState(fd, "online");

        cout << "login success" << endl;
        return true;
    } else {
        std::string errmsg = js["errmsg"];
        cout << errmsg << endl;
        return false;
    }
}
bool MainService::regAck(int fd, json& js) {
    int err_no = js["errno"];
    if (err_no == SUCCESS) {
        int id = js["id"];
        std::string name = js["name"];
        cout << "register successfully, id:" << id << ", name:" << name << endl;
        return true;
    } else {
        return false;
    }
}
bool MainService::addFriendAck(int fd, json& js) {
    int err_no = js["errno"];
    if (err_no == SUCCESS) {
        int friend_id = js["friend_id"];
        std::string friend_name = js["friend_name"];
        std::string friend_state = js["friend_state"];
        User user(friend_id, friend_name, "", friend_state);
        ClientUser::instance()->addFriend(user);
        cout << "add friend successfully" << endl;
        return true;
    } else {
        std::string errmsg = js["errmsg"];
        cout << errmsg << endl;
        return false;
    }
}
bool MainService::removeFriendAck(int fd, json& js) {
    int err_no = js["errno"];
    if (err_no == SUCCESS) {
        int friendid = js["friendid"];
        std::vector<User>& friends = ClientUser::instance()->getFriends();
        auto it = friends.begin();
        while (it != friends.end()) {
            if (it->getId() == friendid) {
                friends.erase(it);
                break;
            }
            ++it;
        }
        cout << "remove friend successfully" << endl;
        return true;
    } else {
        return false;
    }
}
bool MainService::oneChatAck(int fd, json& js) {
    int fromid = js["fromid"];
                            
    if (js.contains("state")) {
        // 上下线消息
        // 更新好友列表状态
        std::vector<User> &friends = ClientUser::instance()->getFriends();
        for (auto &e : friends) {
            if (e.getId() == fromid) {
                e.setState(js["state"]);
                break;
            }
        }
        // 更新群组好友状态
        std::vector<Group>& groups = ClientUser::instance()->getGroups();
        for (auto& group : groups) {
            std::vector<GroupUser>& gusers = group.getUsers();
            for (auto& guser : gusers) {
                if (guser.getId() == fromid) {
                    guser.setState(js["state"]);
                    break;
                }
            }
        }
    } else {
        // 聊天消息
        std::string msg = js["msg"];
        if (fromid == ClientUser::instance()->getCFriendId()) {
            cout << fromid << " say:" << msg << endl;
        } else {
            cout << "a message from " << fromid << endl;
            ClientUser::instance()->addOfflineMsg(fromid, msg);
        }
    }
}
bool MainService::createGroupAck(int fd, json& js) {
    int err_no = js["errno"];
    if (err_no == SUCCESS) {
        int gid = js["gid"];
        std::string gname = js["gname"];
        std::string ginfo = js["ginfo"];
        Group group(gid, gname, ginfo);
        std::vector<GroupUser> gusers;
        GroupUser guser("manager");
        guser.setId(ClientUser::instance()->getId());
        guser.setName(ClientUser::instance()->getName());
        guser.setState("online");
        gusers.push_back(guser);
        group.setUsers(gusers);
        ClientUser::instance()->addGroup(group);
        cout << "create group successfully" << endl;
        return true;
    } else {
        return false;
    }
}
bool MainService::addGroupUserAck(int fd, json& js) {
    int err_no = js["errno"];
    // 将加入的群信息保存到本地
    if (err_no == SUCCESS) {
        std::string group_str = js["group"];
        json group_js = json::parse(group_str);
        int gid = group_js["gid"];
        std::string gname = group_js["gname"];
        std::string info = group_js["info"];
        Group group(gid, gname, info);
        if (js.contains("groupusers")) {
            std::vector<std::string> gusers_str = js["groupusers"];
            std::vector<GroupUser> gusers;
            for (auto& e : gusers_str) {
                json guser_js = json::parse(e);
                std::string grouprole = guser_js["grouprole"];
                int id = guser_js["id"];
                std::string name = guser_js["name"];
                std::string state = guser_js["state"];
                GroupUser guser(grouprole);
                guser.setId(id);
                guser.setName(name);
                guser.setState(state);
                gusers.push_back(guser);
            }
            group.setUsers(gusers);
        }
        ClientUser::instance()->addGroup(group);

        // 通知群里所有的在线群友
        std::vector<Group>& groups = ClientUser::instance()->getGroups();
        for (auto& group : groups) {
            if (group.getId() == gid) {
                std::vector<GroupUser> gusers;
                group.getUsers(gusers);
                for (auto& guser : gusers) {
                    if (guser.getId() != ClientUser::instance()->getId() && guser.getState() == "online") {
                        // 群消息
                    }
                }
            }
        }
        cout << "add group successfully" << endl;
        return true;
    } else {
        return false;
    }
}
bool MainService::groupChatAck(int fd, json& js) {
    int fromid = js["fromid"];
    int gid = js["groupid"];
    std::string msg = js["msg"];

    if (gid == ClientUser::instance()->getCGroupId()) {
        cout << fromid << " say:" << msg << endl;
    } else {
        // 放到离线群消息中
        cout << "a group message from " << gid << "(" << fromid << ")" << endl;
        std::stringstream ss;
        ss << fromid << " say:" << msg;
        ClientUser::instance()->addGroupOfflineMsg(gid, ss.str());
    }
}

/*
    command message
*/
void MainService::commandService(const std::string& msgid, int fd) {
    if (_commandMap.find(msgid) == _commandMap.end()) {
        cout << "input error" << endl;
        cout << "you can view the command through ':man'" << endl;
        cout << endl;
    } else {
        _commandMap[msgid](fd);
    }
}
// 退出
void MainService::quit(int fd) {
    // 通知在线好友, 我已下线
    MainService::instance()->updateFriendState(fd, "offline");
    // 清除本地缓存
    ClientUser::instance()->clearInfos();

    json js;
    js["msgid"] = LOGOUT;
    js["id"] = ClientUser::instance()->getId();

    std::string msg = js.dump();
    msg = std::to_string(msg.size()) + " " + msg;
    tsend(fd, msg.c_str());
}
// 手册
void MainService::man(int fd) {
    for (auto& e : _commandMap) {
        cout << e.first << endl;
    }
    cout << endl;
}
// 好友列表
void MainService::showFriendList(int fd) {
    std::vector<User> friends = ClientUser::instance()->getFriends();
    for (auto& e : friends) {
        cout << e.getId() << ". " << e.getName() << "(" << e.getState() << ")" << endl; 
    }
    cout << endl;
}
// 添加好友
void MainService::addFriend(int fd) {
    int friend_id = 0;
    cout << "friend id:";
    std::cin >> friend_id;
    std::cin.get();

    json js;
    js["msgid"] = ADD_FRIEND;
    js["id"] = ClientUser::instance()->getId();
    js["friendid"] = friend_id;

    std::string msg = js.dump();
    msg = std::to_string(msg.size()) + " " + msg;
    tsend(fd, msg.c_str());
}
// 删除好友
void MainService::removeFriend(int fd) {
    int friend_id = 0;
    cout << "friend id:";
    std::cin >> friend_id;
    std::cin.get();

    json js;
    js["msgid"] = REMOVE_FRIEND;
    js["id"] = ClientUser::instance()->getId();
    js["friendid"] = friend_id;

    std::string msg = js.dump();
    msg = std::to_string(msg.size()) + " " + msg;
    tsend(fd, msg.c_str());
}
// 单聊
void MainService::oneChat(int fd) {
    int toid = 0;
    cout << "toid";
    std::cin >> toid;
    std::cin.get();

    std::vector<User>& friends = ClientUser::instance()->getFriends();
    int len = friends.size();
    int i = 0;
    for (; i < len; ++i) {
        if (friends[i].getId() == toid) {
            break;
        }
    }
    if (i == len) {
        // 没找到该好友
        cout << "id " << toid << " is not your friend or it is not exist..." << endl;
        return;
    }

    // 展示离线消息
    std::unordered_map<int, std::list<std::string>>& offlineMsgMap = ClientUser::instance()->getOfflineMsg();
    if (offlineMsgMap.find(toid) != offlineMsgMap.end()) {
        for (auto& msg : offlineMsgMap[toid]) {
            cout << toid << " say:" << msg << endl;
        }
        offlineMsgMap.erase(toid);
    }

    // 建立对话框
    ClientUser::instance()->setCFriendId(toid);
    while (1) {
        std::string one_msg;
        std::getline(std::cin, one_msg);
        if (one_msg == ":quit") {break;}
        json js;
        js["msgid"] = ONE_CHAT;
        js["fromid"] = ClientUser::instance()->getId();
        js["toid"] = toid;
        js["msg"] = one_msg;

        std::string msg = js.dump();
        msg = std::to_string(msg.size()) + " " + msg;
        tsend(fd, msg.c_str());
    }
    cout << "chat finish" << endl;
    cout << endl;
    ClientUser::instance()->setCFriendId(-1);
}
// 展示群组信息
void MainService::showGroupList(int fd) {
    std::vector<Group>& groups = ClientUser::instance()->getGroups();
    for (auto& group : groups) {
        cout << "===" << group.getId() << ". " << group.getName() << "(" << group.getInfo() << ")" << endl;
        std::vector<GroupUser> gusers;
        group.getUsers(gusers);
        for (auto& guser : gusers) {
            cout << "(" << guser.getGroupRole() << ")" << guser.getId() << ". " << guser.getName() << "(" << guser.getState() << ")" << endl;
        }
    }
    cout << endl;
}
// 创建群组
void MainService::createGroup(int fd) {
    std::string gname;
    std::string ginfo;
    cout << "group name:";
    std::getline(std::cin, gname);
    cout << "group info:";
    std::getline(std::cin, ginfo);

    json js;
    js["msgid"] = CREATE_GROUP;
    js["userid"] = ClientUser::instance()->getId();
    js["name"] = gname;
    js["info"] = ginfo;

    std::string msg = js.dump();
    msg = std::to_string(msg.size()) + " " + msg;
    tsend(fd, msg.c_str());
}
// 加群
void MainService::addGroupUser(int fd) {
    int gid = 0;
    cout << "group id:";
    std::cin >> gid;
    std::cin.get();

    json js;
    js["msgid"] = ADD_GROUPUSER;
    js["userid"] = ClientUser::instance()->getId();
    js["groupid"] = gid;

    std::string msg = js.dump();
    msg = std::to_string(msg.size()) + " " + msg;
    tsend(fd, msg.c_str());
}
// 群消息
void MainService::groupChat(int fd) {
    int gid = 0;
    cout << "group id:";
    std::cin >> gid;
    std::cin.get();

    // 查看是否有该群组
    std::vector<Group>& groups = ClientUser::instance()->getGroups();
    int len = groups.size();
    int i = 0;
    for (; i < len; ++i) {
        if (groups[i].getId() == gid) {
            break;
        }
    }
    if (i == len) {
        cout << "you are not join in this group " << gid << endl;
        return;
    }

    ClientUser::instance()->setCGroupId(gid);
    // 查看是否有离线消息
    std::unordered_map<int, std::list<std::string>>& offlineMsg = ClientUser::instance()->getGroupOfflineMsg();
    auto it = offlineMsg.find(gid);
    if (it != offlineMsg.end()) {
        for (auto& msg : it->second) {
            cout << msg << endl;
        }
        offlineMsg.erase(it);
    }
    while (1) {
        std::string group_msg;
        std::getline(std::cin, group_msg);
        if (group_msg == ":quit") {
            break;
        }
        json js;
        js["msgid"] = GROUP_CHAT;
        js["fromid"] = ClientUser::instance()->getId();
        js["groupid"] = gid;
        js["msg"] = group_msg;

        std::string msg = js.dump();
        msg = std::to_string(msg.size()) + " " + msg;
        tsend(fd, msg.c_str());
    }
    cout << "chat finish" << endl;
    cout << endl;
    ClientUser::instance()->setCGroupId(-1);
}


int main() {
    int fd = tsocket(); 
    tconnect(fd, ip, port);
    while (1)
    {
        int choice = Menu::mainMenu();
        int msgid = 0;
        json js;
        switch (choice) {
        case 1:
            // 登陆
            MainService::instance()->login(fd);
            msgid = response(fd, js);
            if (MainService::instance()->serviceAck(msgid, fd, js)) {
                // 登陆成功
                cout << "you can view the command through ':man'" << endl;

                // 启动读线程(只能启动一次)
                std::call_once(my_once_flag, readFunc, fd);

                while (1) {
                    std::string command;
                    std::getline(std::cin, command);
                    MainService::instance()->commandService(command, fd);
                    if (command == ":quit") {
                        break;
                    }
                }
            }
            break;
        case 2:
            // 注册
            MainService::instance()->reg(fd);
            msgid = response(fd, js);
            MainService::instance()->serviceAck(msgid, fd, js);
            break;
        case 0:
            // 退出
            close(fd);
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}