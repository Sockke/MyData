## chatServer

#### nginx负载均衡器

* nginx负载均衡器的作用

```c++
/*
1. 将client请求, 通过负载均衡算法, 分发到具体的业务服务器上
2. 容灾性, 通过心跳机制来检测业务服务器是否正常
3. 可扩展性, 能够检测到新添加的业务服务器, 保证业务服务器的横向扩展
*/
```

* nginx的环境搭建

```c++
// 下载nginx源码包, 并在/usr/local/下进行解压缩
tar -zxvf nginx-1.12.2.tar.zip
```

```c++
// 检测系统环境, 生成指定的makefile文件
/*
nginx在1.9版本之前, 只支持http协议的web服务器的负载均衡, 1.9版本后开始支持tcp长连接的负载均衡.
但是nginx默认没有编译tcp负载均衡模块, 需要加入--with-stream来激活这个模块
*/
./configure --with-stream
```

```c++
// 编译与安装, 安装需要在root权限下, 因为需要向系统中写入文件
make && make install
```

```nginx
// nginx负载均衡的配置, nginx.conf
# 配置负载均衡模块
stream {
    upstream MyServer {
        # 业务服务器的ip与port, 权重, 最大连接失败次数, 连接超时时间
		server 127.0.0.1:9001 weight=1 max_fails=3 fail_timeout=30s;
		server 127.0.0.1:9002 weight=1 max_fails=3 fail_timeout=30s;
	}

    server {
        listen 8000; # nginx负载均衡器监听的端口号
  		proxy_pass MyServer; # nginx负载均衡器将请求分发的服务器组
    }
}

http {
    include       mime.types;                                         
    default_type  application/octet-stream;
	...
```



#### redis

* redis的作用

```c++
/*
1. redis是一个基于key-value形式的缓存系统, 数据是缓存在内存中的, 保证了性能,
并且redis可以周期性的将内存中的数据持久化到磁盘中
2. redis支持主从同步, 通过发布-订阅模式实现数据从主服务器同步到其他从属服务器上, 可以解决集群部署下跨服务器通信的问题
3. 在redis-server上, 业务服务器通过subscribe订阅channel, 当其他业务服务器通过publish向channel中发布消息时, 订阅了该channel的业务服务器就会获取到消息, 再响应给客户端.
解决了集群部署中跨服务器通信的问题.
*/
```

* redis的环境搭建

```c++
// 通过系统自带的包管理工具安装, 或下载源码包安装
yum install redis
```

```c++
// 启动redis-server
service redis start
systemctl start redis
```

```c++
// 设置开机自启
chkconfig redis on
systemctl enable redis.service
```

* redis的使用

```c++
// 启动redis客户端
redis-cli
```

```c++
// 数据缓存
// 设置key-value
set 1 "192.168.163.99"
set 2 "192.168.163.100"
// 获取value
get 1
get 2
```

```c++
// 发布-订阅模式, 消息中间件
// 订阅消息, 阻塞等待
subscribe 1
// 发布消息
publish 1 "hello world"
```

* redis客户端编程(C++)

```c++
// 安装hiredis源码包, 进行编译与安装
git clone https://github.com/redis/hiredis 
make && make install
```

```c++
#ifndef REDIS_H
#define REDIS_H

#include <iostream>
#include <string>
#include <hiredis/hiredis.h>
#include <thread>
#include <functional>

using std::cout;
using std::endl;

/*
基于同步的发布-订阅模型的redis客户端编程

成员变量:
1. 需要定义2个context, 分别是publish_context与subscribe_context
因为在subscribe时, 同步的redis是阻塞等待消息的发布, 因此subscribe与publish不能在同一个context中
2. _notify_message_handler为事件到来时的消息回调

成员函数:
1. connect连接redis-server, 同时为publish_context与subscribe_context连接redis-server,
然后启动一个独立的线程, 专门用来监听channel上的事件
2. publish发布消息, 直接通过redisCommand执行redis命令
3. subscribe与unsubscribe, 订阅与取消订阅消息, 不能直接通过redisCommand, 因为会阻塞worker线程, 需要将redisCommand的执行进行分离.
	redisAppendCommand将redis命令放到缓冲区中
	redisBufferWrite循环将缓冲区中的命令发送到redis-server中
	redisGetReply阻塞监听事件(封装在observer_channel_message中, 在connect启动的独立线程中调用)
4. observer_channel_message, 初始化消息回调
*/

class Redis {
public:
    Redis();
    ~Redis();

    // 连接redis服务器 
    bool connect();

    // 向redis指定的通道channel发布消息
    bool publish(int channel, std::string message);

    // 向redis指定的通道subscribe订阅消息
    bool subscribe(int channel);

    // 向redis指定的通道unsubscribe取消订阅消息
    bool unsubscribe(int channel);

    // 在独立线程中接收订阅通道中的消息
    void observer_channel_message();

    // 初始化向业务层上报通道消息的回调对象
    void init_notify_handler(std::function<void(int, std::string)> fn);

private:
    // hiredis同步上下文对象，负责publish消息
    redisContext *_publish_context;

    // hiredis同步上下文对象，负责subscribe消息
    redisContext *_subscribe_context;

    // 回调操作，收到订阅的消息，给service层上报
    std::function<void(int, std::string)> _notify_message_handler;
};

#endif
```

#### json

* json的优势

```c++
/*
通过json来完成网络数据的序列化与反序列化

1. 性能上, json是以字符串的形式存储的, 格式进行了压缩, 减少了带宽(格式的压缩, 就是将key与value分离开来)
2. 使用上, json使用起来比较简单, 减少了服务端与客户端数据解析的成本
*/
```

* json的使用

```c++
/*
	JSON for Modern C++, 是一个优秀的json第三方库
*/
#include <iostream>
#include "json.hpp"
using namespace std;

int main() {
    json js;
    js["name"] = "Gehry";
    js["age"] = 18;
    js["gender"] = "male";
    // 序列化
    string msg = js.dump();
    cout << msg << endl;
    
    // 反序列化
    js = json::parse(msg);
    if (js.contains("name")
       && js.contains("age")
       && js.contains("gender")) {
        string name = js["name"];
        int age = js["age"];
        string gender = js["gender"];
        cout << name << " " << age << " " << gender << endl;
    }
    
    return 0;
}
```

#### 数据库

* 表的设计

```mysql
# user表
Create Table: CREATE TABLE `user` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `passwd` varchar(50) NOT NULL,
  `state` enum('online','offline') DEFAULT 'offline',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8
```

```mysql
# friends表
Create Table: CREATE TABLE `friends` (
  `userid` int(11) NOT NULL,
  `friendid` int(11) NOT NULL,
  PRIMARY KEY (`userid`,`friendid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
```

```mysql
# offlinemsg表
Create Table: CREATE TABLE `offlinemsg` (
  `userid` int(11) NOT NULL,
  `message` varchar(500) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8
```

```mysql
# groups表
Create Table: CREATE TABLE `groups` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `info` varchar(200) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8
```

```mysql
# groupuser表
Create Table: CREATE TABLE `groupuser` (
  `userid` int(11) NOT NULL,
  `groupid` int(11) NOT NULL,
  `grouprole` enum('manager','normal') NOT NULL DEFAULT 'normal',
  PRIMARY KEY (`userid`,`groupid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
```

#### 服务端的设计

![](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200430194319419.png)

* 网络模块

```c++
/*
基于moduo网络库, 来屏蔽网络模块
*/
```

* 数据模块

```c++
/*
对数据库的操作, 封装在model类中, 来屏蔽数据模块
*/
```

* 业务模块

```c++
/*
保证软件设计的开闭原则, 通过hash映射, 根据key来匹配对应的业务逻辑函数
1. 在网络模块中, 当拿到网络数据并反序列化后, 得到业务逻辑函数所需的参数信息
直接通过hash匹配对应的业务逻辑函数
2. 当需要增加其他的业务时, 只需要在业务层注册新的业务逻辑函数即可, 不需要在网络层做任何的修改
*/
```

#### CMake

* 用途

```cmake
# 用来构建自动编译的环境的工具
```

* 项目目录树

```
forChat
├── bin
│   ├── chatClient
│   └── chatServer
├── build
├── CMakeLists.txt
├── include
│   ├── client
│   │   ├── chatClient.hpp
│   │   ├── clientUser.hpp
│   │   ├── menu.hpp
│   │   └── tcpsocket.hpp
│   ├── common.hpp
│   ├── group.hpp
│   ├── server
│   │   ├── chatServer.hpp
│   │   ├── chatService.hpp
│   │   ├── db
│   │   │   └── db.hpp
│   │   ├── model
│   │   │   ├── chatModel.hpp
│   │   │   ├── friendModel.hpp
│   │   │   ├── groupModel.hpp
│   │   │   ├── offlineModel.hpp
│   │   │   └── userModel.hpp
│   │   └── redis
│   │       └── redis.hpp
│   └── user.hpp
├── src
│   ├── client
│   │   ├── chatClient.cpp
│   │   ├── clientUser.cpp
│   │   ├── CMakeLists.txt
│   │   ├── menu.cpp
│   │   └── tcpsocket.cpp
│   ├── CMakeLists.txt
│   ├── group.cpp
│   ├── server
│   │   ├── chatServer.cpp
│   │   ├── chatService.cpp
│   │   ├── CMakeLists.txt
│   │   ├── db
│   │   │   └── db.cpp
│   │   ├── model
│   │   │   ├── friendModel.cpp
│   │   │   ├── groupModel.cpp
│   │   │   ├── offlineModel.cpp
│   │   │   └── userModel.cpp
│   │   └── redis
│   │       └── redis.cpp
│   └── user.cpp
├── test
│   └── server.cpp
└── thirdparty
    └── json.hpp
```



* 使用

./CMakeLists.txt

```cmake
# cmake支持的最小的版本
cmake_minimum_required(VERSION 2.0)

# 工程的名字
project(forChat)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

include_directories(${PROJECT_SOURCE_DIR}/include/client)

# 配置链接库的搜索目录
link_directories(/usr/lib64/mysql)

# 加载子目录
add_subdirectory(src)                  
```

./src/CMakeLists.txt

```cmake
# 加载子目录
add_subdirectory(server)

add_subdirectory(client)
```

/src/server/CMakeLists.txt

```cmake
# 定义变量, 表示当前文件夹下的所有的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_SRC_LIST)
aux_source_directory(./model MODEL_SRC_LIST)
aux_source_directory(./redis REDIS_SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_COMMON_LIST)
set(SRC_MAIN ${PROJECT_SOURCE_DIR}/test/server.cpp)

# 生成可执行文件
add_executable(chatServer ${SRC_LIST} ${DB_SRC_LIST} ${MODEL_SRC_LIST} ${REDIS_SRC_LIST} ${SRC_COMMON_LIST} ${SRC_MAIN})

# 配置链接库
target_link_libraries(chatServer muduo_net muduo_base mysqlclient hiredis pthread)
```



#### 问题

* 网络模块

```c++
/*
tcp的粘包问题:
1. muduo网络库在传输层是基于tcp实现的, 需要解决粘包问题
2. 客户端连续发送多个请求到缓冲区中造成粘包问题, 服务端网络模块需要将拿到的网络数据进行分离, 并将每个请求分发到对应的业务服务函数中
3. 可以将网络数据添加长度信息, 或者直接根据json的自述性根据格式来分离数据
*/
```

* 数据模块

```c++
/*

*/
```

* 业务模块

```c++
/*

*/
```





