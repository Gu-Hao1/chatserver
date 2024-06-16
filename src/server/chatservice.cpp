#include <iostream>
#include <muduo/base/Logging.h> //muduo库的日志 头文件

#include "chatservice.hpp"
#include "public.hpp"
#include <vector>
#include <map>
using namespace std;
using namespace muduo;

// 返回唯一实例对象
ChatService *ChatService::getinstance()
{
    // 为了线程安全，使用这样实现单例模式
    static ChatService _instance;
    return &_instance;
}

// 注册消息，以及对应的回调操作
ChatService::ChatService()
{
    // 用户基本业务管理相关事件处理回调注册
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REGIST_MSG, std::bind(&ChatService::regist, this, _1, _2, _3)});
    _msgHandlerMap.insert({ONE_CHAT_MSG, std::bind(&ChatService::oneChat, this, _1, _2, _3)});
    _msgHandlerMap.insert({ADD_FRIEND_MSG, std::bind(&ChatService::addFriend, this, _1, _2, _3)});

    // 群组业务管理相关事件处理回调注册
    _msgHandlerMap.insert({CREAR_GROUP_MSG, std::bind(&ChatService::createGroup, this, _1, _2, _3)});
    _msgHandlerMap.insert({ADD_GROUP_MSG, std::bind(&ChatService::addGroup, this, _1, _2, _3)});
    _msgHandlerMap.insert({GROUP_CHAT_MSG, std::bind(&ChatService::groupChat, this, _1, _2, _3)});

    _msgHandlerMap.insert({LOGINOUT_MSG, std::bind(&ChatService::loginout, this, _1, _2, _3)});

    // 连接redis服务器
    if (_redis.connect())
    {
        // 设置上报消息的回调
        _redis.init_notify_handler(std::bind(&ChatService::handleRedisSubscribeMessage, this, _1, _2));
    }
}

// 服务器异常，业务重置方法
void ChatService::reset()
{
    // 把online状态的用户，设置为offline
    _usermodel.resetState();
}
// 获取消息对应的处理器
MsgHandler ChatService::getHandler(int msgid)
{
    // 记录错误日志:msgid没有对应的事件处理回调
    auto it = _msgHandlerMap.find(msgid);
    if (it == _msgHandlerMap.end())
    {

        // 返回一个默认的处理器,空操作 使用lambda表达式
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp)
        {
            // 错误类型输出
            LOG_ERROR << "msgid:" << msgid << " can no find handler!";
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}
// 处理登录业务
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int id = js["id"];
    string pwd = js["password"];

    // 根据id去查询用户的数据
    User user = _usermodel.query(id);

    if (user.getId() == id && user.getPwd() == pwd)
    {
        if (user.getState() == "online")
        {
            // 该用户已经登录，不允许重复登录
            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 2;
            response["errmsg"] = "this account is using ,input another!";
            conn->send(response.dump());
        }
        else
        {
            // 加一个作用域，减小锁的力度
            {
                lock_guard<mutex> lock(_connMutex);
                // 登录成功，记录用户的连接信息（需要注意线程安全问题）
                _userConnMap.insert({id, conn});
            }

            // id用户登录成功之后向redis中订阅通道channel id
            _redis.subscribe(id);

            // 登录成功，更新用户的状态信息
            user.setState("online");
            // 刷新该用户的状态信息
            _usermodel.updateState(user);

            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 0; // 错误码0：表示的是消息正确
            response["id"] = user.getId();
            response["name"] = user.getName();
            response["state"] = user.getState();

            // 查询该用户是否有离线消息
            vector<string> vec = _OfflineMsgModel.query(id);
            if (!vec.empty())
            {
                response["offlinemsg"] = vec;
                // 读取该用户的离线消息后，把该用户的所有的离线消息删除掉
                _OfflineMsgModel.remove(id);
            }

            // 查询该用户的好友信息并返回
            vector<User> userVec = _friendModel.query(id);
            if (!userVec.empty())
            {
                vector<string> vec2;
                for (User &user : userVec)
                {
                    json js;
                    js["id"] = user.getId();
                    js["name"] = user.getName();
                    js["state"] = user.getState();
                    vec2.push_back(js.dump());
                }
                response["friends"] = vec2;
            }

            // 查询该用户的群组返回
            vector<Group> GroupuserVec = _groupModel.queryGroups(id);
            if (!GroupuserVec.empty())
            {
                // group:[{groupid:[xxx,xxx,xxx,xxx]}]
                vector<string> groupV;
                for (Group &group : GroupuserVec)
                {
                    json groupjs;
                    groupjs["id"] = group.getId();
                    groupjs["groupname"] = group.getGroupName();
                    groupjs["groupdesc"] = group.getGroupdesc();

                    vector<string> userV;
                    // 获取群组中的用户
                    for (GroupUser &user : group.getUsers())
                    {
                        json js;
                        js["id"] = user.getId();
                        js["name"] = user.getName();
                        js["state"] = user.getState();
                        js["role"] = user.getRole();
                        userV.push_back(js.dump());
                    }
                    groupjs["users"] = userV;
                    groupV.push_back(groupjs.dump());
                }
                response["groups"] = groupV;
            }

            conn->send(response.dump()); // 将回答发送给客户端
        }
    }
    else
    {
        // 登录失败：用户不存在或者用户存在但是密码错误
        json response;
        response["msgid"] = LOGIN_MSG_ACK;
        response["errno"] = 1; // 错误码1：表示的是消息错误
        if (user.getId() == -1)
        {
            response["errmsg"] = "The user is not exist!";
        }
        else
        {
            response["errmsg"] = "Your password is not true!";
        }
        conn->send(response.dump());
    }
}

// 处理注册业务
void ChatService::regist(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    string name = js["name"];
    string pwd = js["password"];
    User user;
    user.setName(name);
    user.setPwd(pwd);
    bool state = _usermodel.insert(user);
    if (state)
    {
        // 注册成功
        json response;
        response["msgid"] = REGIST_MSG_ACK;
        response["errno"] = 0; // 错误码0：表示的是消息正确
        response["id"] = user.getId();
        conn->send(response.dump()); // 将回答发送给客户端
        LOG_INFO << "register successfully";

        // // 注册成功直接登录成功的接口（可以跳转到登录界面）
        // json jst;
        // jst["id"] = user.getId();
        // jst["password"] = pwd;
        // login(conn, jst, time);
    }
    else
    {
        // 注册失败
        json response;
        response["msgid"] = REGIST_MSG_ACK;
        response["errno"] = 1; // 错误码1：表示的是消息错误
        conn->send(response.dump());
    }
}

// 处理客户端异常退出
void ChatService::clientCloseException(const TcpConnectionPtr &conn)
{
    // 在存储连接的哈希map表中查询异常退出的socket
    User user;
    {
        lock_guard<mutex> lock(_connMutex);

        for (auto it = _userConnMap.begin(); it != _userConnMap.end(); ++it)
        {
            if (it->second == conn)
            {
                user.setId(it->first);
                _userConnMap.erase(it);
                break;
            }
        }
    }

    // 用户注销，相当于就是相当于下线，在redis中取消订阅通道
    _redis.unsubscribe(user.getId());

    // 更新用户的状态信息
    if (user.getId() != -1)
    {
        user.setState("offline");
        _usermodel.updateState(user);
    }
}
// 处理用户注销业务
void ChatService::loginout(const TcpConnectionPtr &conn, json &js, Timestamp)
{
    int userid = js["id"].get<int>();
    {
        lock_guard<mutex> lock(_connMutex);
        auto it = _userConnMap.find(userid);
        if (it != _userConnMap.end())
        {
            _userConnMap.erase(it);
        }
    }
    // 用户注销，相当于就是小下线，在redis中取消订阅通道
    _redis.unsubscribe(userid);

    User user(userid, "", "", "offline");
    _usermodel.updateState(user);
}

// 处理一对一聊天业务
void ChatService::oneChat(const TcpConnectionPtr &conn, json &js, Timestamp)
{
    // 获取目标用户的id
    int toid = js["to"].get<int>();

    // 作用域控制锁的粒度
    {
        lock_guard<mutex> lock(_connMutex);
        auto it = _userConnMap.find(toid);
        if (it != _userConnMap.end())
        {
            // 目标用户toid在线
            // 服务器主动推送消息给toid目标用户
            it->second->send(js.dump());
            return;
        }
    }

    // 集群的时候会进行修改（有可能目标用户在另一个服务器上）

    // 查询toid是否在线
    User user = _usermodel.query(toid);
    // 说明不不在同一台服务器上
    if (user.getState() == "online")
    {
        _redis.publish(toid, js.dump());
        return;
    }

    // toid 不在线,存储离线消息
    _OfflineMsgModel.insert(toid, js.dump());
}

// 添加好友业务 magid id friendid
void ChatService::addFriend(const TcpConnectionPtr &conn, json &js, Timestamp)
{
    int userid = js["id"].get<int>();
    int friendid = js["friendid"].get<int>();
    // 存储好友信息
    _friendModel.insert(userid, friendid);

    // 可以增加接口来返回给用户好友更新的信息表
}

// 创建群组
void ChatService::createGroup(const TcpConnectionPtr &conn, json &js, Timestamp)
{
    int userid = js["id"].get<int>();
    string groupname = js["groupname"];
    string groupdesc = js["groupdesc"];

    // 存储新创建的群组信息
    Group group(-1, groupname, groupdesc);

    if (_groupModel.createGroup(group))
    {
        // 存储群组创建人的信息
        _groupModel.addGroup(userid, group.getId(), "creator");
    }
}
// 加入群组业务
void ChatService::addGroup(const TcpConnectionPtr &conn, json &js, Timestamp)
{
    int userid = js["id"].get<int>();
    int groupid = js["groupid"].get<int>();
    // 没有响应后续可以加响应
    _groupModel.addGroup(userid, groupid, "normal");
}

// 群组聊天业务
void ChatService::groupChat(const TcpConnectionPtr &conn, json &js, Timestamp)
{
    int userid = js["id"].get<int>();
    int groupid = js["groupid"].get<int>();

    // 首先根据userid查询出群组中除了自己userid的其他的用户的id
    vector<int> uservec = _groupModel.queryGroupUsers(userid, groupid);

    // 加锁
    lock_guard<mutex> lock(_connMutex);

    for (int id : uservec)
    {
        auto it = _userConnMap.find(id);
        if (it != _userConnMap.end())
        {
            // 直接转发群消息
            it->second->send(js.dump());
            // LOG_INFO<<"send message";
        }
        else
        {
            // 查询id是否在线
            User user = _usermodel.query(id);
            if (user.getState() == "online")
            {
                _redis.publish(id, js.dump());
            }
            else
            {
                // 存储离线消息
                _OfflineMsgModel.insert(id, js.dump());
            }
        }
    }
}

// 开服务器通讯的回调函数--从redis消息队列中获取订阅的消息
void ChatService::handleRedisSubscribeMessage(int userid, string msg)
{
    // 加锁
    lock_guard<mutex> lock(_connMutex);
    auto it = _userConnMap.find(userid);
    if (it != _userConnMap.end())
    {
        it->second->send(msg);
        return;
    }

    // 存储用户的离线消息
    _OfflineMsgModel.insert(userid, msg);
}