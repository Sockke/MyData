#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>

#include <zookeeper/zookeeper.h>
#include "xmlConfig.h"

using std::cout;
using std::endl;

class ZkClient {
  public:
    ZkClient();
    void start();
    // zk创建节点
    void create(const char* path, const char* data, int datalen, int state = 0);
    // zk获取节点的值
    std::string get(const std::string& path);
    // 发送心跳
    void sendHeartBeat();

    // 设置根节点路径
    static void setRootNodePath(const std::string& path);
    // 获取根节点路径
    static std::string getRootNodePath();

    // 设置watcher回调
    static void watcher(zhandle_t* zh, int type, int state 
        , const char* path, void* watcherCtx);
  private:
    zhandle_t* _zhandle; // zkClient与zkServer通信的句柄
    static sem_t _sem;
    // rpc服务的根节点
    static std::string _rootNodePath;
};
