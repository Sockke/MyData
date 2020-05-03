#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <string>
#include <vector>

#include "user.hpp"

class GroupUser : public User {
public:
    GroupUser(const std::string& grouprole = "normal");
    std::string getGroupRole() const;
private:
    std::string _grouprole;
};

class Group {
public:
    Group(int id=-1, const std::string& name="", const std::string& info="");
    void setId(int id);
    void setName(const std::string& name);
    void setInfo(const std::string& info);
    void setUsers(std::vector<GroupUser>& users);

    int getId() const;
    std::string getName() const;
    std::string getInfo() const;
    void getUsers(std::vector<GroupUser>& users) const;
    std::vector<GroupUser>& getUsers();
private:
    int _id; // 群组id
    std::string _name; // 群组名
    std::string _info; // 群组的信息
    std::vector<GroupUser> _users; // 群组的成员
};


#endif