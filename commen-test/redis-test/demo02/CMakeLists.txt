# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(redis_demo)

# 设置 C++ 标准：C++11 起步，满足 unique_ptr、using 别名、stoi 等语法需求
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制要求标准，不降级
set(CMAKE_CXX_EXTENSIONS OFF)        # 禁用编译器非标准扩展

# --------------------------
# 查找 hiredis 依赖库
# --------------------------
# 查找头文件路径
find_path(HIREDIS_INCLUDE_DIR 
    NAMES hiredis/hiredis.h
    PATHS /usr/include /usr/local/include
)

# 查找动态库文件
find_library(HIREDIS_LIBRARY 
    NAMES hiredis
    PATHS /usr/lib /usr/local/lib
)

# 依赖检查：没找到就直接报错提示
if(NOT HIREDIS_INCLUDE_DIR)
    message(FATAL_ERROR "未找到 hiredis 头文件，请先安装 libhiredis-dev")
endif()
if(NOT HIREDIS_LIBRARY)
    message(FATAL_ERROR "未找到 hiredis 库文件，请先安装 libhiredis-dev")
endif()

# --------------------------
# 生成可执行文件
# --------------------------
add_executable(redis_demo main.cc)

# 引入 hiredis 头文件目录
target_include_directories(redis_demo PRIVATE ${HIREDIS_INCLUDE_DIR})

# 链接 hiredis 库
target_link_libraries(redis_demo PRIVATE ${HIREDIS_LIBRARY})
