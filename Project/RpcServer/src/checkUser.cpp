#include "../include/checkUser.h"

// 自定义继承了 基于protobuf定义的rpc服务对象
// 重写指定的rpc方法
// 1. 在request中获取参数列表
// 2. 调用本地的方法
// 3. 将返回值设置到response中
// 4. 调用响应回调
void CheckUser::login(google::protobuf::RpcController* controller,
    const LoginRequest* request,
    LoginResponse* response,
    google::protobuf::Closure* done) {
  // 在request获取参数
  std::string uname = request->username();
  std::string passwd = request->password();
  bool ret = login(uname, passwd);
  // 在response设置返回值
  response->set_isloginsuccessfully(ret);
  // 服务方法调用完之前回调done, 主要是负责网络回复, 在框架中实现
  done->Run();
}
void CheckUser::reg(google::protobuf::RpcController* controller,
    const RegRequest* request,
    RegResponse* response,
    google::protobuf::Closure* done) {

}

bool CheckUser::login(const std::string& uname, const std::string& passwd) {
  // 数据库中查询
  if (uname == "sock" && passwd == "5631076") {
    return true;
  }
  return false;
}
bool CheckUser::reg(const std::string& uname, const std::string& passwd, int age, int gender) {
  // 判断合法性
  // 存入数据库
  return true;
}
