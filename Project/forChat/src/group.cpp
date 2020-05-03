#include "group.hpp"

GroupUser::GroupUser(const std::string& grouprole) 
    :  _grouprole(grouprole)
{}
std::string GroupUser::getGroupRole() const {
    return _grouprole;
}


Group::Group(int id, const std::string& name, const std::string& info)
    : _id(id)
    , _name(name)
    , _info(info)
{}
void Group::setId(int id) {_id = id;}
void Group::setName(const std::string &name) {_name = name;}
void Group::setInfo(const std::string &info) {_info = info;}
void Group::setUsers(std::vector<GroupUser>& users) {_users = users;}

int Group::getId() const {return _id;}
std::string Group::getName() const {return _name;}
std::string Group::getInfo() const {return _info;}
void Group::getUsers(std::vector<GroupUser> &users) const {users = _users;}
std::vector<GroupUser>& Group::getUsers() {return _users;}
