cmake_minimum_required(VERSION 3.10)
project(redis_test CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自动查找 hiredis 头文件和库文件
find_path(HIREDIS_INCLUDE_DIR hiredis/hiredis.h)
find_library(HIREDIS_LIBRARY hiredis)

add_executable(redis_demo main.cc)

target_include_directories(redis_demo PRIVATE ${HIREDIS_INCLUDE_DIR})
target_link_libraries(redis_demo PRIVATE ${HIREDIS_LIBRARY})
