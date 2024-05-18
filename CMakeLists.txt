# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(ano_protocol VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/ano_protocol)

# 源文件列表
set(SOURCES
    ${PROJECT_SOURCE_DIR}/ano_protocol/ano_protocol.cpp
    ${PROJECT_SOURCE_DIR}/main.cpp
)

# 可执行文件
add_executable(ano_protocol ${SOURCES})

# 可以选择性地添加调试信息或编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ano_protocol PRIVATE -g)
endif()
