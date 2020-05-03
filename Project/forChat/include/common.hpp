#ifndef COMMON_H
#define COMMON_H

// msgid 业务类型
enum {
    LOGIN = 1, // 登陆
    LOGIN_ACK, // 登陆响应
    REG, // 注册
    REG_ACK, // 注册响应消息类型
    
    LOGOUT, // 退出登录

    ONE_CHAT, // 单聊消息
    
    ADD_FRIEND, // 添加好友
    ADD_FRIEND_ACK, // 添加好友响应
    REMOVE_FRIEND, // 移除好友
    REMOVE_FRIEND_ACK, // 移除好友响应

    CREATE_GROUP, // 创建群组
    CREATE_GROUP_ACK, // 创建群组响应
    ADD_GROUPUSER, // 添加群友
    ADD_GROUPUSER_ACK, // 添加群友响应
    REMOVE_GROUPUSER, // 移除群友
    REMOVE_GROUPUSER_ACK, // 移除群友响应
    GROUP_CHAT, // 群消息
    GROUP_CHAT_ACK, // 群消息响应
};

// errno 错误类型
enum {
    SUCCESS, // 成功
    FAILED, // 失败
    REPEAT_LOGIN, // 重复登陆
    WRONG_PWD //密码错误
};

#endif