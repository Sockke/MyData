#include "userModel.hpp"
#include "db.hpp"
/*
UserModel
*/

// 用户注册
bool UserModel::insert(User& user) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, passwd, state) values('%s', '%s', '%s');", 
        user.getName().c_str(), user.getPasswd().c_str(), user.getState().c_str());
    
    // 修改数据库
    if (sql_conn.update(sql)) {
        int id = mysql_insert_id(sql_conn.getConnection());
        if (id != 0) {
            // 更新用户的id
            user.setId(id);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// 用户查询
bool UserModel::find(User& user) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d;", user.getId());

    // 查询数据库
    MYSQL_RES* result = sql_conn.query(sql);
    if (result != nullptr) {
        MYSQL_ROW row = mysql_fetch_row(result);
        while (row != nullptr) {
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setPasswd(row[2]);
            user.setState(row[3]);

            row = mysql_fetch_row(result);
        }
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
}

// 用户状态更新
bool UserModel::updateState(User& user) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }
    char sql[1024] = {0};
    sprintf(sql, "update user set state = '%s' where id = %d;", user.getState().c_str(), user.getId());

    // 修改数据库
    if (sql_conn.update(sql)) {
        return true;
    } else {
        return false;
    }
}

// 用户状态重置
void UserModel::resetState() {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return;
    }
    const char* sql = "update user set state = 'offline' where state = 'online';";
    sql_conn.update(sql);
}