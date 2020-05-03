#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <mysql/mysql.h>

using std::cout;
using std::endl;

#define TB_NAME "login"
#define MAX_SQL_LEN 1024


class Connection {
  public:
    Connection();
    ~Connection();
    // 数据库连接
    bool connect(const std::string& ip, 
        const std::string& name, 
        const std::string& passwd,
        const std::string& database,
        int port);
    // 数据库增删改
    void DML(const std::string& sql);
    void setStartTime();
    clock_t getAliveTime() const;
  private:
    MYSQL _mysql;
    clock_t _aliveTime;
};
