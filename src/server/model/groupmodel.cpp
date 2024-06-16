
#include "groupmodel.hpp"
#include <string>
#include <vector>
#include "db.h"
#include <muduo/base/Logging.h> //muduo库的日志 头文件
#include"groupuser.hpp"
using namespace std;

// 维护群组信息的操作接口方法

// 创建群组
bool GroupModel::createGroup(Group &group)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into allgroup(groupname,groupdesc) values('%s','%s')", group.getGroupName().c_str(), group.getGroupdesc().c_str());

    MySQL mysql;

    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 获取自动生成的id
            group.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }
    return false;
}
// 加入群组
void GroupModel::addGroup(int userid, int groupid, string role)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser values(%d,%d,'%s')", groupid, userid, role.c_str());

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
// 查询用户所在群组信息
vector<Group> GroupModel::queryGroups(int userid)
{
    /*
    1.先根据userid在groupuser表中查询出该用户所属的群组的信息
    2.再根据群组信息，查询属于该用户的所有的userid,并且和user表进行多表联合查询，查询用户的详细信息
    */
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.groupname,a.groupdesc from allgroup a inner join groupuser b on a.id =b.groupid where b.userid = %d", userid);

    MySQL mysql;
    
    //存储查询出来userid所在的群组
    vector<Group> groupVec;
    if (mysql.connect())
    {
        // sql语句的查询结果 MYSQL_RES
        MYSQL_RES *res = mysql.query(sql);
        // 判断是否查询出来结果
        if (res != nullptr)
        {
            // 讲查询结果按行取出
            MYSQL_ROW row;
            // userid所有的群组信息
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                Group group;
                group.setId(atoi(row[0]));
                group.setGroupName(row[1]);
                group.setGroupdesc(row[2]);
                groupVec.push_back(group);
            }
            // 释放资源
            mysql_free_result(res);
        }
    }
    else
    {
        LOG_INFO << "database no connect!!";
    }

    // 查询每个群组中的用户信息
    for (Group &group : groupVec)
    {
        sprintf(sql, "select a.id,a.name,a.state,b.grouprole from user a inner join groupuser b on a.id =b.userid where b.groupid = %d", group.getId());

        MySQL mysql;

        // 存储查询出来的所有的离线消息
        vector<Group> groupVec;
        if (mysql.connect())
        {
            // sql语句的查询结果 MYSQL_RES
            MYSQL_RES *res = mysql.query(sql);
            // 判断是否查询出来结果
            if (res != nullptr)
            {
                // 讲查询结果按行取出
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res)) != nullptr)
                {
                    GroupUser user;
                    user.setId(atoi(row[0]));
                    user.setName(row[1]);
                    user.setState(row[2]);
                    user.setRole(row[3]);

                    //将该群组中的所有的用户放入该群组的数组属性vector<GroupUser>中
                    group.getUsers().push_back(user);
                }
                // 释放资源
                mysql_free_result(res);
            }
        }
        else
        {
            LOG_INFO << "database no connect!!";
        }
    }
    return groupVec;
}

// 根据指定的groupid查询用户id列表，除userid自己，主要用户群聊业务给群组其他成员群发消息
vector<int> GroupModel::queryGroupUsers(int userid, int groupid)
{
        // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select userid from groupuser where groupid = %d and userid != %d", groupid, userid);

    vector<int>idVec;
    MySQL mysql;

    // 存储查询出来的所有的离线消息
    vector<Group> groupVec;
    if (mysql.connect())
    {
        // sql语句的查询结果 MYSQL_RES
        MYSQL_RES *res = mysql.query(sql);
        // 判断是否查询出来结果
        if (res != nullptr)
        {
            // 讲查询结果按行取出
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                idVec.push_back(atoi(row[0]));
            }
            // 释放资源
            mysql_free_result(res);
        }
    }
    return idVec;
}
