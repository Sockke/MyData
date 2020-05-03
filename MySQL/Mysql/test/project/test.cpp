#include "sql_control.h"
#include <unordered_map>

void getLoginInfo(std::unordered_map<std::string, std::string>& info) {
  MysqlOperator mySQL;
  mySQL.Insert(info["name"], info["passWd"], info["phoneNum"]);
}

int main() {
  //std::unordered_map<std::string, std::string> info;
  //info["name"] = "laoma";
  //info["passWd"] = "123";
  //info["phoneNum"] = "12345678911";
  //getLoginInfo(info);
  MysqlOperator mySQL;
  std::string info;
  bool ret = mySQL.Query(info, "liuchen");
  if (ret == false) {
    cout << "没有该用户" << endl;
  }
  cout << "liuchen:" << info << endl;
  return 0;
}
