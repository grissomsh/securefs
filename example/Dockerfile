# 使用 Ubuntu 20.04 作为基础镜像
FROM ubuntu:20.04

# 设置环境变量，避免交互式安装提示
ENV DEBIAN_FRONTEND=noninteractive

# 备份原始 sources.list 文件并替换为国内镜像源，安装依赖
RUN cp /etc/apt/sources.list /etc/apt/sources.list.bak && \
    sed -i 's|http://archive.ubuntu.com/ubuntu/|http://mirrors.aliyun.com/ubuntu/|g' /etc/apt/sources.list && \
    sed -i 's|http://security.ubuntu.com/ubuntu/|http://mirrors.aliyun.com/ubuntu/|g' /etc/apt/sources.list && \
    apt update && \
    apt install -y --no-install-recommends libfuse-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY securefs /usr/bin/securefs

# 复制启动脚本到容器中
COPY entrypoint.sh /usr/local/bin/entrypoint.sh

# 确保启动脚本具有可执行权限
RUN chmod +x /usr/local/bin/entrypoint.sh

# 设置启动脚本为容器的默认入口点
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
