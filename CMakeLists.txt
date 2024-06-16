cmake_minimum_required(VERSION 3.0) #要求cmake的最低版本号
project(Chat) #定义当前的工程名

#配置编译选项
set(CMAKE_BUILD_TYPE "Debug")#设置debug模式，如果没有这一行将不能调试设断点
#加-g的选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g) 

# 设置可执行文件最终存储的路径
# 含义是在当前目录的bin目录下
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

#加载子目录
add_subdirectory(src)#去目录src下去找MakeLists.txt文件
