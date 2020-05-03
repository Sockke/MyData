#include "sql_connection.h"


Connection::Connection() {
  mysql_init(&_mysql); // 初始化数据库句柄
}
Connection::~Connection() {
  mysql_close(&_mysql);
}
// 数据库连接
bool Connection::connect(const std::string& ip, 
    const std::string& name, 
    const std::string& passwd,
    const std::string& database,
    int port) {
  MYSQL* ret = mysql_real_connect(&_mysql, ip.c_str(), name.c_str(), passwd.c_str(),
      database.c_str(), port, nullptr, 0);
  return ret != nullptr;
}
// 数据库增删改
void Connection::DML(const std::string& sql) {
  int ret = mysql_query(&_mysql, sql.c_str());
  if (ret != 0) {
    cout << "mysql query error:" << mysql_error(&_mysql) << endl;
  }
}

// 更新开始时间
void Connection::setStartTime() {
  _aliveTime = clock();
}
// 获取空闲时间
clock_t Connection::getAliveTime() const {
  return clock() - _aliveTime;
}
