#include "friendmodel.hpp"

#include "db.h"

// 插入好友关系
void FriendModel::insert(int userid, int friendid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into friend values(%d,%d)", userid,friendid);

    char sql1[1024] = {0};
    sprintf(sql1, "insert into friend values(%d,%d)", friendid,userid);

    MySQL mysql;

    if (mysql.connect())
    {
        mysql.update(sql);
        mysql.update(sql1);
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
}

// 返回用户的好友列表
vector<User> FriendModel::query(int userid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid = a.id where b.userid=%d", userid);

    MySQL mysql;

    // 存储查询出来的所有的离线消息
    vector<User> vec;
    if (mysql.connect())
    {
        // sql语句的查询结果 MYSQL_RES
        MYSQL_RES *res = mysql.query(sql);
        // 判断是否查询出来结果
        if (res != nullptr)
        {
            // 讲查询结果按行取出
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))!= nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vec.push_back(user);
            }
            // 释放资源
            mysql_free_result(res);
            return vec;
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
    return vec;
}