#include "offlineModel.hpp"
#include "db.hpp"

/*
OfflineMsgModel
*/

// 离线消息的添加
bool OfflineMsgModel::insert(int userid, const std::string &msg) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemsg values(%d, '%s');", userid, msg.c_str());

    if (sql_conn.update(sql)) {
        // 添加成功
        return true;
    } else {
        return false;
    }
}
// 离线消息的移除
bool OfflineMsgModel::remove(int userid) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemsg where userid = %d;", userid);

    if (sql_conn.update(sql)) {
        // 移除成功
        return true;
    } else {
        return false;
    }
}
// 离线消息的获取
bool OfflineMsgModel::find(int userid, std::vector<std::string> &msgs) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemsg where userid = %d;", userid);

    // 查询数据库
    MYSQL_RES* result = sql_conn.query(sql);
    if (result != nullptr) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            msgs.push_back(row[0]);
        }
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
}
