#include "offlinemessagemodel.hpp"
#include "db.h"
#include <muduo/base/Logging.h> //muduo库的日志 头文件
// 存储用户的离线消息
void OfflineMsgModel::insert(int userid, string msg)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values(%d,'%s')", userid, msg.c_str());

    MySQL mysql;

    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return;
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
    return;
}
// 删除用户的离线消息
void OfflineMsgModel::remove(int userid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemessage where userid=%d", userid);

    MySQL mysql;

    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return;
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
    return;
}

// 查询用户的离线消息（离线消息可能不是只有一个，所以使用list进行消息存储）
vector<string> OfflineMsgModel::query(int userid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid = %d", userid);

    MySQL mysql;

    // 存储查询出来的所有的离线消息
    vector<string> vec;
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
                vec.push_back(row[0]);
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
