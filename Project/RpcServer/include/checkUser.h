#pragma once
#include <iostream>
#include <string>

#include "../test/checkService.pb.h"

// 本地服务:
// 1. 在protobuf文件中定义service, 包括服务及方法, 生成pb文件
// 2. 定义本地服务类, 该类必须继承在protobuf文件中定义好的service
// 3. 在该类中重写指定的服务方法
//  1). 在request中获取参数
//  2). 调用本地方法
//  3). 通过response设置返回值
//  4). 调用回调函数done->Run();
//
// 本地服务只需要关注逻辑代码的实现, 
// 具体的网络数据的组织和传输交给protobuf的序列化与反序列化
// 具体的rpc分发调用交给rpc服务框架

class CheckUser : public CheckServiceRpc {
  public: 
    // 重写基于protobuf的服务方法
    virtual void login(google::protobuf::RpcController* controller,
        const LoginRequest* request,
        LoginResponse* response,
        google::protobuf::Closure* done);
    virtual void reg(google::protobuf::RpcController* controller,
        const RegRequest* request,
        RegResponse* response,
        google::protobuf::Closure* done);

    // 本地方法
    bool login(const std::string& uname, const std::string& passwd);
    bool reg(const std::string& uname, const std::string& passwd, int age, int gender);
};
