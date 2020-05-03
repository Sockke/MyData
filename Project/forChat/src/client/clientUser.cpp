#include "clientUser.hpp"


ClientUser* ClientUser::instance() {
    static ClientUser user;
    return &user;
}
ClientUser::ClientUser()
    : _cfriendid(-1)
    , _cgroupid(-1)
{}
// 设置用户信息
void ClientUser::setUser(User& user) {
    _user = user;
}
// 获取用户id
int ClientUser::getId() const {
    return _user.getId();
}
std::string ClientUser::getName() const {
    return _user.getName();
}
// 添加好友
void ClientUser::addFriend(User& user) {
    _friends.push_back(user);
}
// 添加离线消息
void ClientUser::addOfflineMsg(int fromid, const std::string& msg) {
    _offlineMsg[fromid].push_back(msg);
}
// 添加群组
void ClientUser::addGroup(Group& group) {
    _groups.push_back(group);
}
// 添加群组离线消息
void ClientUser::addGroupOfflineMsg(int groupid, const std::string& msg) {
    _groupOfflineMsg[groupid].push_back(msg);
}

// 获取好友列表
std::vector<User>& ClientUser::getFriends() {return _friends;}
// 获取离线消息
std::unordered_map<int, std::list<std::string>>& ClientUser::getOfflineMsg() {return _offlineMsg;}
// 获取群组信息
std::vector<Group>& ClientUser::getGroups() {return _groups;}
// 获取群组离线消息
std::unordered_map<int, std::list<std::string>>& ClientUser::getGroupOfflineMsg() {return _groupOfflineMsg;}

int ClientUser::getCFriendId() const{return _cfriendid;}
void ClientUser::setCFriendId(int id) {_cfriendid = id;}
int ClientUser::getCGroupId() const {return _cgroupid;}
void ClientUser::setCGroupId(int id) {_cgroupid = id;}

// 清除本地缓存
void ClientUser::clearInfos() {
    _friends.clear();
    _groups.clear();
    _offlineMsg.clear();
    _groupOfflineMsg.clear();
    _cfriendid = -1;
    _cgroupid = -1;
}