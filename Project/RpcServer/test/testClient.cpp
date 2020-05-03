#include "../include/rpcClient.h"

int main() {
  CheckServiceRpc_Stub stub(new RpcClient());
  LoginRequest req;
  LoginResponse rsp;
  req.set_username("sock");
  req.set_password("5631076");
  stub.login(nullptr, &req, &rsp, nullptr);
  bool ret = rsp.isloginsuccessfully();
  if (ret == true) {
    cout << "登陆成功..." << endl;
  } else {
    cout << "登陆失败..." << endl;
  }
  return 0;
}
