#!/bin/bash

# 定义加密目录和挂载点
ENC_DIR="/encrypted"
MOUNT_DIR="/mnt/secure"

# 确保目录存在
mkdir -p "$ENC_DIR" "$MOUNT_DIR"

# 检查是否已经创建加密文件系统
if [ ! -f "$ENC_DIR/.securefs.json" ]; then
    echo "Creating a new encrypted filesystem in $ENC_DIR"
    securefs create "$ENC_DIR" --pass "your-password"
fi

# 挂载加密文件系统
echo "Mounting encrypted filesystem from $ENC_DIR to $MOUNT_DIR"
securefs mount -b "$ENC_DIR" "$MOUNT_DIR" --pass "your-password"

# 设置挂载目录的权限，仅允许当前用户访问
chmod 700 "$MOUNT_DIR"

# 捕获退出信号，确保容器停止时卸载加密文件系统
trap "securefs unmount $MOUNT_DIR; exit" SIGINT SIGTERM

# 启动容器的主要进程
exec "$@"
