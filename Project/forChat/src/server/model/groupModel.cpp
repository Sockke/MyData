#include "groupModel.hpp"
#include "db.hpp"

/*
GroupModel
*/
// 群组的创建
bool GroupModel::create(Group& group) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "insert into groups(name, info) values('%s', '%s');", group.getName().c_str(), group.getInfo().c_str());

    if (sql_conn.update(sql)) {
        // 创建成功
        int id = mysql_insert_id(sql_conn.getConnection());
        group.setId(id);
        return true;
    } else {
        return false;
    }
}
// 组员的添加
bool GroupModel::insert(int userid, int groupid, Group& group, const std::string& grouprole) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser values(%d, %d, '%s');", userid, groupid, grouprole.c_str());

    if (sql_conn.update(sql)) {
        // 添加成功
        if (group.getId() == -1) {
            char sql_find[1024] = {0};
            sprintf(sql_find, "select name, info from groups where id = %d", groupid);
            MYSQL_RES* result = sql_conn.query(sql_find);
            if (result != nullptr) {
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)) != nullptr) {
                group.setName(row[0]);
                group.setInfo(row[1]);
                }
                mysql_free_result(result);
            }   
        }
        return true;
    } else {
        return false;
    }
}
// 组员的移除
bool GroupModel::remove(int userid, int groupid) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }    
    char sql[1024] = {0};
    sprintf(sql, "delete from groupuser where userid=%d and groupid=%d;", userid, groupid);

    if (sql_conn.update(sql)) {
        // 移除成功
        return true;
    } else {
        return false;
    }
}
// 所有群组信息的查看
bool GroupModel::findGroups(int userid, std::vector<Group>& groups)  {
    // 获取每个组的信息
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.info from groups a inner join groupuser b on a.id = b.groupid where b.userid=%d;", userid);

    // 查询数据库
    MYSQL_RES* result = sql_conn.query(sql);
    if (result != nullptr) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            Group group(atoi(row[0]), row[1], row[2]);
            groups.push_back(group);
        }
        mysql_free_result(result);

        // 获取每个组的成员信息
        for (auto& group : groups) {
            std::vector<GroupUser> gusers;
            char sql_user[1024] = {0};
            sprintf(sql_user, "select a.id,a.name,a.state,b.grouprole from user a inner join groupuser b on a.id = b.userid where b.groupid = %d;", group.getId());
            MYSQL_RES* result_user = sql_conn.query(sql_user);
            if (result_user != nullptr) {
                MYSQL_ROW row_user;
                while ((row_user = mysql_fetch_row(result_user)) != nullptr) {
                    GroupUser guser(row_user[3]);
                    guser.setId(atoi(row_user[0]));
                    guser.setName(row_user[1]);
                    guser.setState(row_user[2]);
                    gusers.push_back(guser);
                }
                mysql_free_result(result_user);
            } else {
                return false;
            }
            group.setUsers(gusers);
        }

        return true;
    } else {
        return false;
    }
}

// 群组成员的获取
bool GroupModel::findGroupUsers(int userid, int groupid, std::vector<int>& userids) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }
    char sql[1024] = {0};
    sprintf(sql, "select userid from groupuser where groupid = %d and userid != %d;", groupid, userid);

    // 查询数据库
    MYSQL_RES* result = sql_conn.query(sql);
    if (result != nullptr) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            userids.push_back(atoi(row[0]));
        }
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
}

// 群组成员信息的获取
bool GroupModel::findGroupUsersInfo(int groupid, std::vector<GroupUser>& users) {
    // 组装sql
    DB sql_conn;
    if (!sql_conn.connect()) {
        return false;
    }
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state,b.grouprole from user a inner join groupuser b on a.id = b.userid where b.groupid = %d;", groupid);

    // 查询数据库
    MYSQL_RES* result = sql_conn.query(sql);
    if (result != nullptr) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            GroupUser guser(row[3]);
            guser.setId(atoi(row[0]));
            guser.setName(row[1]);
            guser.setState(row[2]);
            users.push_back(guser);
        }
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }   
}