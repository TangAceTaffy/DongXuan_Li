#!/bin/bash

# 1. 清理 build 目录
if [ -d "build" ]; then
    echo "正在清理 build 目录..."
    rm -rf build/*
else
    echo "创建 build 目录..."
    mkdir build
fi

# 2. 生成 CMake 配置
echo "正在生成 CMake 配置..."
cmake -B build || { echo "CMake 配置失败！"; exit 1; }

# 3. 编译项目
echo "正在编译项目..."
cmake --build build || { echo "编译失败！"; exit 1; }

# 4. 检查可执行文件
if [ ! -f "./build/main" ]; then
    echo "Error: ./build/main not found!"
    exit 1
fi

# 5. 传输到远程主机
if scp ./build/main root@192.168.43.98:/home/root/;then
    echo "传输成功  $(date '+%Y-%m-%d %H:%M:%S')"
else
    echo "传输失败"
    exit 1
fi