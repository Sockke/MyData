#ifndef OFFLINEMODEL_H
#define OFFLINEMODEL_H

#include <iostream>
#include <string>
#include <vector>

//offlinemsg表的操作
class OfflineMsgModel {
public:
    // 离线消息的添加
    bool insert(int userid, const std::string& msg);
    // 离线消息的移除
    bool remove(int userid);
    // 离线消息的获取
    bool find(int userid, std::vector<std::string>& msgs);
};

#endif