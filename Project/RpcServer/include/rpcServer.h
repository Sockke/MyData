#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

#include "google/protobuf/service.h" // 有关服务的头文件
#include "google/protobuf/descriptor.h" // 有关服务或方法描述的头文件
#include "google/protobuf/message.h" // 有关request与response信息的头文件

#include "zkClient.h"
#include "xmlConfig.h"

using std::cout;
using std::endl;

using namespace muduo;
using namespace muduo::net;

// rpc服务器的实现:
// protobuf不仅可以实现序列化的数据结构, 
// 而且内部还提供了rpc服务接口, 支持rpc编程
//
// rpc服务端:
// 1. 注册rpc服务, 建立服务和服务方法的映射,
// 并且将服务注册到zookeeper上
// 2. 响应rpc调用, 
//  1)对rpc调用请求信息进行解析, 获取服务及方法, 参数信息
//  2)在映射表中查找方法, 根据方法获取rpc消息对象, 
//  将参数反序列化到request中, 将调用完成后的回调函数绑定到response中
//  3)调用服务的CallMethod方法进行rpc分发调用

class RpcServer {
  public:
    // 获取唯一实例
    static RpcServer* getInstance();
    void start();
    // 服务和服务方法的注册
    void serviceRegister(google::protobuf::Service* service);
  private:
    RpcServer(EventLoop* loop, const InetAddress& addr);
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp cometime);
    // 响应回调
    void sendRpcResponse(const TcpConnectionPtr& conn, 
        google::protobuf::Message* response);
  private:
    EventLoop* _loop;
    TcpServer _server;

    // 服务信息
    struct ServiceInfo {
      google::protobuf::Service* _service; // 服务对象指针
      std::unordered_map<std::string, 
        const google::protobuf::MethodDescriptor*> _methodMap; // 方法映射
    };
    std::unordered_map<std::string, ServiceInfo> _serviceMap; // 服务映射

    // 唯一实例
    //static RpcServer* _rpcServer;
    // zk客户端
    ZkClient _zkClient;
};
