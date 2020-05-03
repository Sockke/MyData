# CRPC

基于muduo库和protobuf协议实现的RPC远程调用分布式框架
网络部分使用muduo库, 数据序列化与反序列化以及RPC定义交给protobuf, 服务配置中心采用zookeeper

# 环境

Linux后端开发, 需要安装muduo网络库, protobuf协议库, zookeeper, tinyxml第三方库等

# 项目介绍

1. lib: RPC生成的静态库, 以及tinyxml生成的动态库, 可以直接链接使用
2. include: RPC分布式框架的头文件信息
3. src: RPC分布式框架的源码信息
4. thirdparty: 第三方库tinyxml
5. test: 测试代码, 创建的服务, 服务端以及客户端
6. bin: test测试文件生成的的可执行文件
7. config: 配置文件

# 编译

保证操作系统环境安装了muduo, protobuf以及zookeeper, 直接make一键编译在bin目录下生成可执行文件

# 运行

1. 启动zookeeper服务器
2. 配置config下的rpc_cfg.xml配置文件, 修改服务端IP及端口信息, 以及zookeeper客户端连接服务端的IP及端口信息.
3. 启动srv, RPC服务端
4. 启动cli, RPC客户端
