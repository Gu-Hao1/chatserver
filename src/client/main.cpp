#include <json.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <unordered_map>

using namespace std;
using json = nlohmann::json;
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <atomic>

#include "group.hpp"
#include "user.hpp"
#include "public.hpp"

// 记录当前的用户信息
User g_currentUser;
// 记录当前用户的好友列表
vector<User> g_currentUserFriendList;
// 记录当前登录用户的群组列表信息
vector<Group> g_currentUserGroupList;

bool isMainMenuRunning = false;

// 用于读写线程之间的通信(信号量)
sem_t rwsem;

// 记录登录状态（true:登录成功 false:登录失败）(是一个原子类型)
atomic_bool g_isLoginSuccess;

// 显示当前登录成功用户的基本的信息
void showCurrentuserData();

// 接收线程
void readTaskHandler(int clientfd);

// 获取系统时间（聊天信息需要添加时间信息）
string getCurrentTime();

// 主聊天页面程序
void mainMenu(int);

// 显示当前登录成功用户的基本的信息
void showCurrentuserData()
{
    cout << "========================login user================" << endl;
    cout << "current login user => id:" << g_currentUser.getId() << "name:" << g_currentUser.getName() << " State:" << g_currentUser.getState() << endl;
    cout << "------------------------friend list---------------" << endl;
    if (!g_currentUserFriendList.empty())
    {
        for (User &user : g_currentUserFriendList)
        {
            cout << user.getId() << " " << user.getName() << " " << user.getState() << endl;
        }
    }
    cout << "------------------------group list---------------" << endl;
    if (!g_currentUserGroupList.empty())
    {
        for (Group &group : g_currentUserGroupList)
        {
            cout << group.getId() << " " << group.getGroupName() << " " << group.getGroupdesc() << endl;
            for (GroupUser &user : group.getUsers())
            {
                cout << user.getId() << " " << user.getName() << " " << user.getState() << " " << user.getRole() << endl;
            }
        }
    }
    cout << "====================================================" << endl;
}

// 聊天客户端程序的实现，main线程用作发送线程，子线程用作接收线程
int main(int argc, char **argv)
{
    // 判断参数的个数是否是够的----程序名字+ip+port
    if (argc < 3)
    {
        cerr << "command invalid! example: /ChatClient 127.0.0.1 6000" << endl;
        exit(-1);
    }

    // 解析通过命令行参数传递的Ip和port
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);

    // 创建客户端的socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == clientfd)
    {
        cerr << "socket create error" << endl;
    }

    // 填写client需要连接的server的信息ip+port
    sockaddr_in server;
    memset(&server, 0, sizeof(sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    // client和server进行连接
    if (-1 == connect(clientfd, (sockaddr *)&server, sizeof(sockaddr_in)))
    {
        cerr << "connect server error" << endl;
        close(clientfd);
        exit(-1);
    }

    // 成功连接服务器
    // main线程用于接收用户的输入，负责发送数据
    for (;;)
    {
        // 显示首页菜单，登录，注册，退出
        cout << "=========================" << endl;
        cout << "1.login" << endl;
        cout << "2.register" << endl;
        cout << "3.quit" << endl;
        cout << "=========================" << endl;
        cout << "choice:";
        int choice = 0;
        cin >> choice;
        cin.get(); // 读掉缓冲区残留的回车

        // 初始化信号量
        sem_init(&rwsem, 0, 0);
        // 开启子线程负责接收服务器的返回数据
        std::thread readTask(readTaskHandler, clientfd); // pthread_create
        readTask.detach();

        switch (choice)
        {
        case 1:
            // login业务
            {
                /*
                // 该用户已经登录，不允许重复登录
                response["msgid"] = LOGIN_MSG_ACK;
                response["errno"] = 2;
                */
                int id = 0;
                char pwd[50] = {0};
                cout << "userid:";
                cin >> id;
                cin.get(); // 读掉缓冲区残留的回车
                cout << "userpassword:";
                cin.getline(pwd, 50);

                /*
                    int id = js["id"];
                    string pwd = js["password"];
                */
                json js;
                js["msgid"] = LOGIN_MSG;
                js["id"] = id;
                js["password"] = pwd;
                string request = js.dump();

                g_isLoginSuccess = false;

                int len = send(clientfd, request.c_str(), strlen(request.c_str()) + 1, 0);
                if (len == -1)
                {
                    cerr << "send login msg error:" << request << endl;
                }
                // 等待信号量，由子线程处理完登陆的的响应消息之后，通知这里
                sem_wait(&rwsem);
                if (g_isLoginSuccess)
                {
                    isMainMenuRunning = true;
                    // 进入聊天主菜单界面
                    mainMenu(clientfd);
                }
            }
            break;
        case 2:
            // regist业务
            {
                // 注册需要用户名+密码
                char name[50] = {0};
                char pwd[50] = {0};
                cout << "username:";
                cin.getline(name, 50); // 名字中间可能存在空格，防止读不完
                cout << "userpassword:";
                cin.getline(pwd, 50); // 名字中间可能存在空格，防止读不完

                json js;
                js["msgid"] = REGIST_MSG;
                js["name"] = name;
                js["password"] = pwd;

                string requestmsg = js.dump(); // json字符串序列化

                int len = send(clientfd, requestmsg.c_str(), strlen(requestmsg.c_str()) + 1, 0);
                if (len == -1)
                {
                    cerr << "send reg msg error:" << requestmsg << endl;
                }

                sem_wait(&rwsem);
            }
            break;
        case 3:
            // quit业务
            {
                close(clientfd);
                sem_destroy(&rwsem); // 释放信号量资源
                exit(0);
            }
        default:
            cerr << "invalid input!" << endl;
        }
    }
    return 0;
}

// "help" command handler
void help(int fd = 0, string str = "");
// "chat" command handler
void chat(int, string);
// "addfriend" command handler
void addfriend(int, string);
// "creategroup" command handler
void creategroup(int, string);
// "addgroup" command handler
void addgroup(int, string);
// "groupchat" command handler
void groupchat(int, string);
// "loginout" command handler
void loginout(int, string);

// 系统支持的客户端的命令列表
unordered_map<string, string> commandMap = {
    {"help", "显示所有的支持命令,格式help"},
    {"chat", "一对一聊天,格式chat:friendid:message"},
    {"addfriend", "添加好友,格式addfriend:friendid"},
    {"creategroup", "创建群组,格式creategroup:groupname:groupdesc"},
    {"addgroup", "加入群组,格式addgroup:groupid"},
    {"groupchat", "群聊,格式groupchat:groupid:message"},
    {"loginout", "注销,格式loginout"},
};

// 注册系统支持的客户端的命令列表
// int:是clientfd
// string:是客户端输入的消息
unordered_map<string, function<void(int, string)>>
    commandHandlerMap = {
        {"help", help},
        {"chat", chat},
        {"addfriend", addfriend},
        {"creategroup", creategroup},
        {"addgroup", addgroup},
        {"groupchat", groupchat},
        {"loginout", loginout},
};

// 主聊天页面程序
void mainMenu(int clientfd)
{
    help();

    char buffer[1024] = {0};
    while (isMainMenuRunning)
    {
        cin.getline(buffer, 1024);
        // 字符数组转为字符串类型
        string commandbuf(buffer);
        string command; // 存储命令
        int index = commandbuf.find(":");
        if (-1 == index)
        {
            command = commandbuf;
        }
        else
        {
            command = commandbuf.substr(0, index);
        }
        auto it = commandHandlerMap.find(command);
        if (it == commandHandlerMap.end())
        {
            cerr << "invalid input command!" << endl;
            continue;
        }
        // 调用相应的事件处理回调，mainMenu对修改封闭，添加新功能不需要修改函数
        it->second(clientfd, commandbuf.substr(index + 1, commandbuf.size() - index));
    }
}
// "help" command handler
void help(int fd, string str)
{
    // 输出帮助
    cout << "show command list >>> " << endl;
    for (auto &p : commandMap)
    {
        cout << p.first << " : " << p.second << endl;
    }
    cout << endl;
}

// "chat" command handler
void chat(int clientfd, string str)
{
    int index = str.find(":"); // friendid:message
    if (-1 == index)
    {
        cerr << "chat command invalid" << endl;
        return;
    }
    int friendid = atoi(str.substr(0, index).c_str());
    string messge = str.substr(index + 1, str.size() - index);

    json js;
    js["msgid"] = ONE_CHAT_MSG;
    js["id"] = g_currentUser.getId();
    js["name"] = g_currentUser.getName();
    js["to"] = friendid;
    js["msg"] = messge;
    js["time"] = getCurrentTime();

    string buffer = js.dump();

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);

    if (-1 == len)
    {
        cerr << "send chat msg error->" << buffer << endl;
    }
}
// "addfriend" command handler
void addfriend(int clientfd, string str)
{
    // addfriend:friendid
    int friendid = atoi(str.c_str());
    json js;
    js["msgid"] = ADD_FRIEND_MSG;
    js["id"] = g_currentUser.getId();
    js["friendid"] = friendid;
    string buffer = js.dump();

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);

    if (-1 == len)
    {
        cerr << "send addfirend msg error->" << buffer << endl;
    }
}
// "creategroup" command handler
void creategroup(int clientfd, string str)
{
    // creategroup:groupname:groupdesc
    int index = str.find(":");
    if (-1 == index)
    {
        cerr << "creategroup command invalid" << endl;
        return;
    }
    string groupname = str.substr(0, index);
    string groupdesc = str.substr(index + 1, str.size() - index);

    json js;
    js["msgid"] = CREAR_GROUP_MSG;
    js["id"] = g_currentUser.getId();
    js["groupname"] = groupname;
    js["groupdesc"] = groupdesc;

    string buffer = js.dump();

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);

    if (-1 == len)
    {
        cerr << "send creategroup msg error->" << buffer << endl;
    }
}
// "addgroup" command handler
void addgroup(int clientfd, string str)
{
    // "addgroup","加入群组,格式addgroup:groupid"
    int groupid = atoi(str.c_str());
    json js;
    js["msgid"] = ADD_GROUP_MSG;
    js["id"] = g_currentUser.getId();
    js["groupid"] = groupid;
    string buffer = js.dump();

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);

    if (-1 == len)
    {
        cerr << "send addgroup msg error->" << buffer << endl;
    }
}
// "groupchat" command handler
void groupchat(int clientfd, string str)
{
    //"groupchat","群聊,格式groupchat:groupid:message"
    int index = str.find(":"); // groupid:message
    if (-1 == index)
    {
        cerr << "groupchat command invalid" << endl;
        return;
    }
    int groupid = atoi(str.substr(0, index).c_str());
    string messge = str.substr(index + 1, str.size() - index);

    json js;
    js["msgid"] = GROUP_CHAT_MSG;
    js["id"] = g_currentUser.getId();
    js["groupid"] = groupid;
    js["name"] = g_currentUser.getName();

    js["msg"] = messge;
    js["time"] = getCurrentTime();

    string buffer = js.dump();

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);

    if (-1 == len)
    {
        cerr << "send groupchat msg error->" << buffer << endl;
    }
}

// 处理登录响应的业务逻辑
void doLoginResoponse(json &reponsejs)
{
    if (0 != reponsejs["errno"].get<int>()) // 登录失败
    {
        cerr << reponsejs["errmsg"] << endl;
        g_isLoginSuccess = false;
    }
    else // 成功登录
    {
        // 拉取用户的信息到客户端
        // 记录当前的用户信息
        g_currentUser.setId(reponsejs["id"]);
        g_currentUser.setName(reponsejs["name"]);
        g_currentUser.setState(reponsejs["state"]);

        // 记录当前用户的好友列表信息（无法实时更新）
        if (reponsejs.contains("friends"))
        {
            g_currentUserFriendList.clear();
            vector<string> vec = reponsejs["friends"];
            for (string &str : vec)
            {
                json js = json::parse(str);
                User user;
                user.setId(js["id"].get<int>());
                user.setName(js["name"]);
                user.setState(js["state"]);
                g_currentUserFriendList.push_back(user);
            }
        }

        // 记录当前用户的群组列表信息
        if (reponsejs.contains("groups"))
        {
            g_currentUserGroupList.clear();
            vector<string> vec = reponsejs["groups"];
            for (string &groupstr : vec)
            {
                json js = json::parse(groupstr);
                Group group;
                group.setId(js["id"].get<int>());
                group.setGroupName(js["groupname"]);
                group.setGroupdesc(js["groupdesc"]);

                vector<string> vec2 = js["users"];
                for (string &userstr : vec2)
                {
                    GroupUser user;
                    json js = json::parse(userstr);
                    user.setId(js["id"].get<int>());
                    user.setName(js["name"]);
                    user.setState(js["state"]);
                    user.setRole(js["role"]);
                    group.getUsers().push_back(user);
                }

                g_currentUserGroupList.push_back(group);
            }
        }

        // 显示登录用户的基本信息
        showCurrentuserData();

        // 显示当前用户的离线消息 个人聊天消息或者群组消息
        if (reponsejs.contains("offlinemsg"))
        {
            vector<string> vec = reponsejs["offlinemsg"];
            for (string &str : vec)
            {
                json js = json::parse(str);
                // time+[id]+name + " said: "+xxx
                cout << js["time"] << "[" << js["id"] << "]" << js["name"] << " said: " << js["msg"] << endl;
            }
        }
        g_isLoginSuccess = true;
    }
}
// 处理登录响应的业务逻辑
void doRegistResoponse(json &responsejs)
{
    if (0 != responsejs["errno"].get<int>()) // 注册失败
    {
        cerr << "name is already exist,register error!" << endl;
    }
    else
    {
        /*
            response["msgid"] = REGIST_MSG_ACK;
            response["errno"] = 0; // 错误码0：表示的是消息正确
            response["id"] = user.getId();
        */
        cout << "name register sucess,userid is " << responsejs["id"]
             << ", do not forget it!" << endl;
    }
}
// 接收线程--接收服务器转发的信息
void readTaskHandler(int clientfd)
{
    for (;;)
    {
        char buffer[1024] = {0};
        int len = recv(clientfd, buffer, 1024, 0);
        if (-1 == len || 0 == len)
        {
            close(clientfd);
        }

        // 接收ChatServer转发的数据，反序化生成json数据对象
        json js = json::parse(buffer);

        if (ONE_CHAT_MSG == js["msgid"].get<int>())
        {
            cout << js["time"].get<string>() << " [" << js["id"] << "]" << js["name"].get<string>()
                 << " said: " << js["msg"].get<string>() << endl;
            continue;
        }
        if (GROUP_CHAT_MSG == js["msgid"].get<int>())
        {
            cout << "群消息[" << js["groupid"] << "]:" << js["time"].get<string>() << " [" << js["id"] << "]" << js["name"].get<string>()
                 << " said: " << js["msg"].get<string>() << endl;
            continue;
        }

        // 处理登录的响应消息
        if (LOGIN_MSG_ACK == js["msgid"].get<int>())
        {
            // 处理登录响应的业务逻辑
            doLoginResoponse(js);
            sem_post(&rwsem);
            continue;
        }

        if (REGIST_MSG_ACK == js["msgid"].get<int>())
        {
            doRegistResoponse(js);
            sem_post(&rwsem);
            continue;
        }
    }
}

// "loginout" command handler
void loginout(int clientfd, string str)
{
    json js;
    js["msgid"] = LOGINOUT_MSG;
    js["id"] = g_currentUser.getId();
    string buffer = js.dump();

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);

    if (-1 == len)
    {
        cerr << "send loginout msg error->" << buffer << endl;
    }
    else
    {
        isMainMenuRunning = false;
    }
}
// 获取系统时间（聊天信息需要添加时间信息）
string getCurrentTime()
{
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm *ptm = localtime(&tt);
    char date[60] = {0};
    sprintf(date, "%d-%02d-%02d %02d:%02d:%02d", (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1,
            (int)ptm->tm_mday, (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);

    return std::string(date);
}