#ifndef CLIENTUSER_H
#define CLIENTUSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include "user.hpp"
#include "group.hpp"

using std::cout;
using std::endl;

class ClientUser {
public:
    static ClientUser* instance();
    void setUser(User& user);
    int getId() const ;
    std::string getName() const;
    void addFriend(User& user);
    void addGroup(Group& group);
    void addOfflineMsg(int fromid, const std::string& msg);
    void addGroupOfflineMsg(int groupid, const std::string& msg);

    std::vector<User>& getFriends();
    std::unordered_map<int, std::list<std::string>>& getOfflineMsg();
    std::vector<Group>& getGroups();
    std::unordered_map<int, std::list<std::string>>& getGroupOfflineMsg();

    int getCFriendId() const;
    void setCFriendId(int id);
    int getCGroupId() const;
    void setCGroupId(int id);

    void clearInfos();
private:
    ClientUser();
    User _user; // user的信息
    std::vector<User> _friends; // 好友列表
    std::vector<Group> _groups; // 群组列表
    std::unordered_map<int, std::list<std::string>> _offlineMsg; // 离线消息
    std::unordered_map<int, std::list<std::string>> _groupOfflineMsg; // 群离线消息

    int _cfriendid;
    int _cgroupid;
};

#endif