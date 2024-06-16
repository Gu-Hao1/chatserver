#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include"user.hpp"
#include <vector>
#include <muduo/base/Logging.h> //muduo库的日志 头文件
// 维护好友信息的操作接口方法
class FriendModel
{
public:
    //插入好友关系
    void insert(int userid,int friendid);

    //返回用户的好友列表
    vector<User> query(int userid);
private:
};

#endif