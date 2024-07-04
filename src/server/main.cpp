#include"chatserver.hpp"
#include <signal.h>
#include<iostream>
#include"chatservice.hpp"
using namespace std;

//处理服务器crtl+C结束之后，重置所有用户的状态信息
void resetHandler(int)
{
    ChatService::getinstance()->reset();
    exit(0);
}
int main(int argc,char** argv)
{

    // 判断参数的个数是否是够的----程序名字+ip+port
    if (argc < 3)
    {
        cerr << "command invalid! example: /Chatserver 127.0.0.1 port " << endl;
        exit(-1);
    }

    // 解析通过命令行参数传递的Ip和port
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);

    //函数用于设置信号处理函数
    signal(SIGINT,resetHandler);
    /*
        创建服务器对象
    */
    EventLoop loop;//相当于epoll

    InetAddress addr(ip,port);//服务器的地址

    string server_name="ChatServer";//服务器的名称
    
    //创建服务器对象
    ChatServer server(&loop,addr,server_name);

    server.start();//开启服务器服务--listenfd epoll_ctl=>epoll
    loop.loop();//epoll_wait 以阻塞的方式等待新用户的连接，已经连接的用户的读写事件等
}