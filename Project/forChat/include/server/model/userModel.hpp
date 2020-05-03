#ifndef USERMODEL_H
#define USERMODEL_H

#include <iostream>

#include "user.hpp"

// user表的操作
class UserModel {
public:
    // 用户注册
    bool insert(User& user);
    // 用户查询
    bool find(User& user);
    // 用户状态更新
    bool updateState(User& user);
    // 用户状态重置
    void resetState();
};

#endif