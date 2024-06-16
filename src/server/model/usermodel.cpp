#include "usermodel.hpp"

#include <string>
#include <iostream>
using namespace std;
#include "db.h"
#include <muduo/base/Logging.h> //muduo库的日志 头文件
#include "user.hpp"
bool UserModel::insert(User &user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name,password,state) values('%s','%s','%s')", user.getName().c_str(), user.getPwd().c_str(), user.getState().c_str());

    MySQL mysql;

    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 获取插入成功的用户数据的主键id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
    return false;
}
User UserModel::query(int id)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);

    MySQL mysql;

    if (mysql.connect())
    {
        // sql语句的查询结果 MYSQL_RES
        MYSQL_RES *res = mysql.query(sql);
        // 判断是否查询出来结果
        if (res != nullptr)
        {
            // 讲查询结果按行取出
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0])); // row[0]是 char*类型，需要强转为int型
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);
                // 释放资源，查询结果是指针类型，需要进行资源释放
                mysql_free_result(res);
                return user;
            }
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
    // 如果没有查询到结果，返回的是一个默认的User对象
    // User(int id = -1, string name = "", string password = "", string state = "offline");
    return User();
}

bool UserModel::updateState(User user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state = '%s' where id=%d", user.getState().c_str(), user.getId());
    MySQL mysql;

    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
    return false;
}

// 重置所有用户的状态信息
void UserModel::resetState()
{
    // 组装sql语句
    char sql[1024] = "update user set state = 'offline' where state='online'";
    MySQL mysql;

    if (mysql.connect())
    {
        mysql.update(sql);
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
}