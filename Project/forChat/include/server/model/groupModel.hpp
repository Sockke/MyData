#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <iostream>
#include <string>
#include <vector>

#include "group.hpp"

// groups与groupuser表的操作
class GroupModel {
public:
    // 群组的创建
    bool create(Group& group);
    // 组员的添加
    bool insert(int userid, int groupid, Group& group, const std::string& grouprole="normal");
    // 组员的移除
    bool remove(int userid, int groupid);
    // 群组信息的查看
    bool findGroups(int userid, std::vector<Group>& groups);
    // 群组成员的获取
    bool findGroupUsers(int userid, int groupid, std::vector<int>& userids);
    // 群组成员信息的获取
    bool findGroupUsersInfo(int groupid, std::vector<GroupUser>& users);
};

#endif