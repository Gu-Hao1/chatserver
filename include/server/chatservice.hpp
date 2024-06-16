// 服务模块头文件
#ifndef CHARSERVICE_H
#define CHARSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "json.hpp"
using json = nlohmann::json;

#include "redis.hpp"
#include "usermodel.hpp"
#include <mutex>
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *getinstance();

    // 处理注册业务
    void regist(const TcpConnectionPtr &conn, json &js, Timestamp);
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 处理一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 处理用户注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp);

    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);

    // 服务器异常，业务重置方法
    void reset();

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    
    //开服务器通讯的回调函数
    void handleRedisSubscribeMessage(int,string);
    
private:
    // 构造函数私有化
    ChatService();
    // 删除拷贝构造
    ChatService(const ChatService &) = delete;
    // 删除复制运算符的重载
    ChatService &operator=(const ChatService &) = delete;

    // 存储消息id和对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储用户id和该用户的连接（要注意线程安全问题）
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 定义互斥锁,保证_userConnMap的线程安全问题（因为可能是多个线程同时进行操作）
    mutex _connMutex;

    // 数据库操作类对象
    //  表User的操作类对象
    UserModel _usermodel;

    OfflineMsgModel _OfflineMsgModel;

    // 表friend的操作类的对象
    FriendModel _friendModel;

    // 表allgroup和表groupuser的操作类对象
    GroupModel _groupModel;

    Redis _redis;
};

#endif