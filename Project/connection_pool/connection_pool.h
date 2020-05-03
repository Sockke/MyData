#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <atomic>
#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>
#include "sql_connection.h"
using std::cout;
using std::endl;

class ConnectionPool {
  public:
    static ConnectionPool* getPool();
    ~ConnectionPool();
    // 消费连接
    std::shared_ptr<Connection> getConn();
  private:
    ConnectionPool();
    bool loadCfgFile();
    // 生产连接
    void produceConn();
    // 扫描空闲连接
    void scannIdleConn();
  private:
    // 配置文件中的键值对
    std::unordered_map<std::string, std::string> _connMap;    
    // 数据库连接池所需要的成员变量
    int _initConnSize; // 初始连接数量
    int _maxConnSize; // 最大连接数量
    int _maxConnIdleTime; // 连接的最长空闲时间
    int _maxConnTimeout; // 请求连接的最长超时时间

    std::queue<Connection*> _connQueue; // 连接队列
    std::atomic_int _curConnSize; // 当前连接数量

    // 保证线程之间同步通信的变量
    std::mutex _mtx;
    std::condition_variable _conv;
};
