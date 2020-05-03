#include "friendModel.hpp"
#include "db.hpp"

/*
FriendModel
*/
// 好友添加
bool FriendModel::insert(int userid, int friendid, User& user) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "insert into friends values(%d, %d);", userid, friendid);

    if (sql_conn.update(sql)) {
        // 添加成功
        char sql2[1024] = {0};
        sprintf(sql2, "select name,state from user where id = %d;", friendid);
        MYSQL_RES* result = sql_conn.query(sql2);
        if (result != nullptr) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)) != nullptr) {
                user.setName(row[0]);
                user.setState(row[1]);
                break;
            }
            mysql_free_result(result);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
// 好友移除
bool FriendModel::remove(int userid, int friendid) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "delete from friends where userid = %d and friendid = %d;", userid, friendid);

    if (sql_conn.update(sql)) {
        // 移除成功
        return true;
    } else {
        return false;
    }
}
// 好友列表的获取
bool FriendModel::find(int userid, std::vector<User> &friends) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friends b on a.id=b.friendid where b.userid=%d;", userid);

    // 查询数据库
    MYSQL_RES* result = sql_conn.query(sql);
    if (result != nullptr) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            User user;
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setState(row[2]);
            friends.push_back(user);
        }
        mysql_free_result(result);
        //return true;
    } else {
        return false;
    }
    char sql2[1024] = {0};
    sprintf(sql2, "select a.id,a.name,a.state from user a inner join friends b on a.id=b.userid where b.friendid=%d;", userid);
    result = sql_conn.query(sql2);
    if (result != nullptr) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            User user;
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setState(row[2]);
            friends.push_back(user);
        }
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
}