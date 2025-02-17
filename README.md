# chatserver
项目致力于实现高并发、稳定的聊天服务。网络模块采用 Epoll+LT 的 I/O 复用、非阻塞 I/O 和主从 Reactor 模型，搭配 one loop per thread 线程模型与线程池进行设计实现，实现的业务包括用户注册，登录，一对一聊天，群聊等。
