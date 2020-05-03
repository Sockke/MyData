#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <mysql/mysql.h>

using std::cout;
using std::endl;

#define TB_NAME "myLogin"
#define MAX_SQL_LEN 1024


class MysqlOperator {
 public:
    MysqlOperator() {
      mysql_init(&_mysql); // 初始化数据库句柄
      MYSQL* ret = mysql_real_connect(&_mysql, "127.0.0.1", "root", 
          "034917","mypet", 0, nullptr, 0);
      if (ret == nullptr) {
        cout << "mysql connect error:" << mysql_errno(&_mysql) << endl;
        exit(-1);
      }
      // 字符集调整
    }
    ~MysqlOperator() {
      mysql_close(&_mysql);
    }
    // 增
    bool Insert(const std::string& number, const std::string& passwd) {
      char sql[MAX_SQL_LEN] = {0};
      sprintf(sql, "insert into %s values(NULL, '%s', '%s');", 
          TB_NAME, number.c_str(), passwd.c_str());
      int ret = mysql_query(&_mysql, sql);
      if (ret != 0) {
        cout << "mysql insert error:" << mysql_error(&_mysql) << endl;
        return false;
      }
      return true;
    }
    // 删
    bool Delete(const std::string& id) {
      char sql[MAX_SQL_LEN] = {0};
      sprintf(sql, "delete from %s where id = %s;", TB_NAME, id.c_str());
      int ret = mysql_query(&_mysql, sql);
      if (ret != 0) {
        cout << "mysql delete error:" << mysql_error(&_mysql) << endl;
        return false;
      }
      return true;
    }
    // 改
    bool Modify(const std::string& id, const std::string& newNumber, const std::string& newPasswd) {
      char sql[MAX_SQL_LEN] = {0};
      if (!newNumber.empty()) {
        sprintf(sql, "update %s set phone = '%s' where id = %s;", 
            TB_NAME, newNumber.c_str(), id.c_str());
      } else if (!newPasswd.empty()) {
        sprintf(sql, "update %s set number = '%s' where id = %s",
            TB_NAME, newPasswd.c_str(), id.c_str());
      } else {
        cout << "mysql modify with empty field" << endl;
        return false;
      }
      int ret = mysql_query(&_mysql, sql);
      if (ret != 0) {
        cout << "mysql modify error:" << mysql_error(&_mysql) << endl;
        return false;
      }
      return true;
    }
    // 查
    bool Query(std::string& info, const std::string& number) {
      char sql[MAX_SQL_LEN] = {0};
      sprintf(sql, "select password from %s where phone = '%s';", 
          TB_NAME, number.c_str());
      int ret = mysql_query(&_mysql, sql);
      if (ret != 0) {
        cout << "mysql select error:" << mysql_error(&_mysql) << endl;
        return false;
      }
      MYSQL_RES* result = mysql_store_result(&_mysql);
      //int nums = mysql_num_fields(result);
      MYSQL_ROW row = mysql_fetch_row(result);
      info = row[0];
      //while ((row = mysql_fetch_row(result))) {
      //  for (int i = 0; i < nums; ++i) {
      //    info += row[i];
      //    info += " ";
      //  }
      //}
      mysql_free_result(result);
      return true;
    }
  private:
    MYSQL _mysql;
};
