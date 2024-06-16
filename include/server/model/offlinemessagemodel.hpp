#ifndef OFFLINEMWSSAGEMODEL_H
#define OFFLINEMWSSAGEMODEL_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;


class OfflineMsgModel
{
public:
    //存储用户的离线消息
    void insert(int userid,string msg);

    //删除用户的离线消息
    void remove(int userid);

    //查询用户的离线消息（离线消息可能不是只有一个，所以使用list进行消息存储）
    vector<string> query(int userid);

};

#endif