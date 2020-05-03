#include "../include/rpcClient.h"
#include "../include/serviceMethod.pb.h"
#include <functional>
#include <thread>

// 自定义继承了google::protobuf::RpcChannel类的类, 用于构造rpc客户端对象
RpcClient::RpcClient()
  : _client(nullptr)
{}

RpcClient::~RpcClient() {
  delete _client;
  _client = nullptr;
}

void RpcClient::connect() {
  _client->connect();
  _loop.loop();
}
// 所有的rpc调用都会到达这个需要重写的方法中CallMethod
// 1. 该方法在建立连接后发起调用
// 2. 将服务和方法名序列化到字符串中, 将参数列表通过request序列化到字符串中
// 将长度+服务和方法名+参数列表组织成字符串准备发送
// 3. 通过response设置响应回调, 处理得到的返回值
// 4. 阻塞等待连接, 当连接成功后唤醒, 发送请求
void RpcClient::CallMethod(const google::protobuf::MethodDescriptor* method,
    google::protobuf::RpcController* controller,
    const google::protobuf::Message* request,
    google::protobuf::Message* response,
    google::protobuf::Closure* done) {
  // 客户端是单线程, 如果需要使用信号量或条件变量来同步执行过程
  // 需要使用多线程
  //std::thread thr([&]()->void{
      // 需要发送的数据header
      std::string header;
      // 获取服务名和方法名
      const google::protobuf::ServiceDescriptor* service = method->service();
      std::string service_name = service->name();
      std::string method_name = method->name();

      // 通过zk查找rpc服务是否存在
      ZkClient zkClient;
      zkClient.start();
      std::string path = ZkClient::getRootNodePath() + "/" + service_name + "/" + method_name;
      std::string host = zkClient.get(path);
      if (host.empty()) {
        cout << "no service or method:" << service_name << "-" << method_name << endl;
        return;
      }

      // 序列化服务和方法, 设置服务名和方法名
      std::string service_method_str;
      serviceMethod service_method;
      service_method.set_service_name(service_name);
      service_method.set_method_name(method_name);
      service_method.SerializeToString(&service_method_str); // 序列化到字符串中
      // 确定服务名和方法名的长度
      int header_size = service_method_str.size();
      // 序列化参数列表
      std::string args;
      request->SerializeToString(&args);
      // 将服务和方法长度+服务和方法名+参数列表组织在header里面
      // string (const char* s, size_t n); 构造s的前4个字节的数据
      header.insert(0, std::string((char*)&header_size, 4));
      header += service_method_str;
      header += args;
      // 设置获取服务器响应的回调  
      _responseCallBack = [&](std::string& msg)->void{
        // 反序列化响应信息(返回值)
        response->ParseFromString(msg);
      };

      // 设置发起rpc调用的回调
      _sendRpcCallBack = [&](const TcpConnectionPtr& conn)->void{
        conn->send(header);
      };

      // 打印一下
      cout << "service name:" << service_name << endl;
      cout << "method name:" << method_name << endl;
      cout << "args:" << args << endl;

      // 创建TcpClient, 连接RpcServer
      int pos = host.find(":");
      std::string ip = host.substr(0, pos);
      short port = atoi(host.substr(pos + 1).c_str());
      InetAddress addr(ip, port);
      _client = new TcpClient(&_loop, addr, "");
      _client->setConnectionCallback(std::bind(&RpcClient::onConnection, this, _1));
      _client->setMessageCallback(std::bind(&RpcClient::onMessage, this, _1, _2, _3));
      connect();
  //});
  //thr.detach();
}

// 建立连接后唤醒阻塞线程, 发起rpc调用请求
void RpcClient::onConnection(const TcpConnectionPtr& conn) {
  if (conn->connected()) {
    // 执行rpc调用
    _sendRpcCallBack(conn);
  } else {
    conn->shutdown(); // 关闭连接
    _loop.quit(); // 退出事件循环
  }
}

// 调用响应回调, 反序列化字符串到response中, 进行处理
void RpcClient::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp cometime) {
  std::string msg = buf->retrieveAllAsString();
  _responseCallBack(msg); // 调用获取响应结果的回调
  // 做事情
  // ...
}
