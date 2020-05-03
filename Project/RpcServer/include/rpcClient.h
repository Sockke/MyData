#pragma once
#include <iostream>
#include <string>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>

#include "../test/checkService.pb.h"

#include "zkClient.h"

using std::cout;
using std::endl;

using namespace muduo;
using namespace muduo::net;

// 1. 客户端类需要继承RpcChannel重写里面的CallMethod方法,
// 因为客户端的任何rpc调用, 最终都会调用CallMethod方法
//  1) 组织rpc调用信息, 获取服务名方法名, 参数等信息
//  2) 在zookeeper中查看是否有该服务及方法
//  3) 设置2个响应回调, 一个是响应返回结果, 一个是连接成功后发起的rpc调用
//  4) 创建TcpClient, 发起连接, 启动事件循环
//
// 2. 客户端创建指定的服务对象, service_stub, 将RpcChannel交给service_stub处理
// 调用指定的服务方法

class RpcClient : public google::protobuf::RpcChannel {
  public:
    RpcClient();
    ~RpcClient();
    void connect();
    // 执行rpc调用
    virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
        google::protobuf::RpcController* controller,
        const google::protobuf::Message* request,
        google::protobuf::Message* response,
        google::protobuf::Closure* done);
  private:
    void sendRpcResponse(const TcpConnectionPtr& conn, google::protobuf::Message* response);
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp cometime);
  private:
    EventLoop _loop;
    TcpClient* _client;

    std::function<void(std::string&)> _responseCallBack; // 得到服务器响应后的回调
    std::function<void(const TcpConnectionPtr&)> _sendRpcCallBack;
};
