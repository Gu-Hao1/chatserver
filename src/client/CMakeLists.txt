#定义一个SRC_LIST变量 ,包含了该目录下的所有的源文件
aux_source_directory(. SRC_LIST)

aux_source_directory(../server/model MODEL_LIST)

aux_source_directory(../server/db DB_LIST)
#通过本目录下的所有的源文件--生成可执行文件Chatserver 
add_executable(Chatclient ${SRC_LIST} ${MODEL_LIST} ${DB_LIST})

#指定可执行文件链接时需要依赖的库文件
target_link_libraries(Chatclient muduo_net muduo_base mysqlclient pthread)