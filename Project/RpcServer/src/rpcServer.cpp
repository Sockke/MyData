#include "../include/rpcServer.h"
#include "../include/serviceMethod.pb.h"
#include "../include/checkUser.h"
#include <functional>

RpcServer* RpcServer::getInstance() {
  static EventLoop loop;
  static InetAddress addr(XmlConfig::getInstance().getIp(), 
      XmlConfig::getInstance().getPort());
  static RpcServer rpcServer(&loop, addr);
  return &rpcServer;
}

RpcServer::RpcServer(EventLoop* loop, const InetAddress& addr)
  : _loop(loop)
  , _server(loop, addr, "RpcServer")
{
  // 设置回调
  _server.setConnectionCallback(std::bind(&RpcServer::onConnection, this, _1));
  _server.setMessageCallback(std::bind(&RpcServer::onMessage, this, _1, _2, _3));
  // 设置服务端线程数量
  _server.setThreadNum(4);

  // 连接zookeeper
  _zkClient.start();
  // 发送zk心跳, 维护session
  _zkClient.sendHeartBeat();
}

void RpcServer::start() {
  _server.start(); // socket bind listen
  _loop->loop(); // accept, epoll_wait
}

// 向RpcServer注册服务, 以及服务对应的方法
void RpcServer::serviceRegister(google::protobuf::Service* service) {
  const google::protobuf::ServiceDescriptor* service_desc = service->GetDescriptor();
  std::string service_name = service_desc->name(); // 服务名

  // 创建znode服务
  std::string path = _zkClient.getRootNodePath();
  path += ("/" + service_name);
  _zkClient.create(path.c_str(), nullptr, -1);

  // 注册服务对应的服务方法
  ServiceInfo serviceInfo;
  serviceInfo._service = service;
  int method_amount = service_desc->method_count();  // 获取方法数量
  for (int i = 0; i < method_amount; ++i) {
    const google::protobuf::MethodDescriptor* method_desc = service_desc->method(i); // 方法描述
    std::string method_name = method_desc->name();
    serviceInfo._methodMap.insert({method_name, method_desc});

    // 在znode下创建子节点服务方法
    std::string method_path;
    method_path = (path + "/" + method_name);
    _zkClient.create(method_path.c_str(), _server.ipPort().c_str(),
        _server.ipPort().size(), ZOO_EPHEMERAL); // 临时节点
  }
  // 注册服务
  _serviceMap.insert({service_name, serviceInfo});
}

void RpcServer::onConnection(const TcpConnectionPtr& conn) {
  if (!conn->connected()) {
    conn->shutdown(); // close(fp);
  }
}

// 消息的处理回调
// 当rpc请求到达时, 首先先得到网络数据进行解析(长度+服务和方法名+参数列表)
// 通过长度来获取服务和方法名字符串, 然后反序列化到service_method中
// 得到参数列表, 反序列化到request消息对象中
// 设置response响应回调函数, 在函数中实现响应返回值
void RpcServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp cometime) {
  std::string msg = buf->retrieveAllAsString(); // 拿到网络消息
  int header_size = 0;
  // 获取服务和方法信息的大小
  // 从msg的0位置开始, 拷贝4个字节的数据到header_size
  msg.copy((char*)&header_size, sizeof(int), 0); // 一般是配合insert使用
  std::string header = msg.substr(4, header_size);
  // 反序列化
  serviceMethod service_method; 
  service_method.ParseFromString(header); 
  // 在反序列化对象中提取数据, 获取服务名和方法名
  std::string service_name = service_method.service_name();
  std::string method_name = service_method.method_name();
  // 获取参数
  std::string args = msg.substr(4 + header_size);

  // 在map表中查找指定的服务方法的描述
  ServiceInfo serviceInfo = _serviceMap[service_name];
  google::protobuf::Service* service = serviceInfo._service;
  const google::protobuf::MethodDescriptor* method_desc = serviceInfo._methodMap[method_name];
  // 组织成rpc消息
  // 根据服务方法的描述, 来获取rpc消息对象(request为请求rpc消息对象, response为响应rpc消息对象)
  google::protobuf::Message* request = service->GetRequestPrototype(method_desc).New();
  google::protobuf::Message* response = service->GetResponsePrototype(method_desc).New();
  // request反序列化参数列表, 用于获取指定参数
  request->ParseFromString(args);
  // response设置回调, 用于序列化返回值响应客户端
  google::protobuf::Closure* done = 
    google::protobuf::NewCallback<RpcServer, const TcpConnectionPtr&, google::protobuf::Message*>
    (this, &RpcServer::sendRpcResponse, conn, response);

  // 打印一下结果
  cout << "service name:" << service_name << endl;
  cout << "method name:" << method_name << endl;
  cout << "args:" << args << endl;

  // 服务方法的分发
  service->CallMethod(method_desc, nullptr, request, response, done);
}

void RpcServer::sendRpcResponse(const TcpConnectionPtr& conn, 
    google::protobuf::Message* response) {
  // 错误码 + 返回值
  std::string response_msg; 
  response->SerializeToString(&response_msg);
  conn->send(response_msg);
  conn->shutdown();
}
