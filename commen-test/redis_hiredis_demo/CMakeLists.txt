cmake_minimum_required(VERSION 3.10)
project(redis_demo)

# 使用 C++11 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成可执行文件
add_executable(redis_demo main.cpp)

# 链接 hiredis 动态库
target_link_libraries(redis_demo hiredis)

