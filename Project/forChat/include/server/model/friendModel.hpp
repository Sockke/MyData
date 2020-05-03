#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include <iostream>
#include <vector>

#include "user.hpp"

// friends表的操作
class FriendModel {
public:
    // 好友添加
    bool insert(int userid, int friendid, User& user);
    // 好友移除
    bool remove(int userid, int friendid);
    // 好友列表的获取
    bool find(int userid, std::vector<User>& friends);
};

#endif