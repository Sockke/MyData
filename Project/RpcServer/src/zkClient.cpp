#include "../include/zkClient.h"
#include <thread>
#include <chrono>

sem_t ZkClient::_sem;
std::string ZkClient::_rootNodePath = "/RpcService";

ZkClient::ZkClient() : _zhandle(nullptr) {
  sem_init(&_sem, 0, 0);
}

void ZkClient::start() {
  //std::string host = "127.0.0.1:2181";
  std::string host = XmlConfig::getInstance().getZookeeperHost();
  int timeout = XmlConfig::getInstance().getTimeout();
  _zhandle = zookeeper_init(host.c_str(), watcher, timeout, nullptr, nullptr, 0);
  if (_zhandle == nullptr) {
    cout << "connect zookeeper error" << endl;
    exit(EXIT_FAILURE);
  }
  // 阻塞等待连接成功
  sem_wait(&_sem);
  cout << "connect zookeeper success" << endl;
}

void ZkClient::create(const char* path, const char* data, int datalen, int state) {
  // 判断zk节点是否存在, 不存在再创建
  int flag = zoo_exists(_zhandle, path, 0, nullptr);
  if (flag == ZNONODE) {
    std::string path_buf(128, 0);
    flag = zoo_create(_zhandle, path, data, datalen, 
        &ZOO_OPEN_ACL_UNSAFE, state, &path_buf[0], path_buf.size());
    if (flag == ZOK) {
      cout << "znode create success, path:" << path << endl;
    } else {
      cout << "znode create failed, path:" << path << endl;
      cout << "flag:" << flag << endl;
      exit(EXIT_FAILURE);
    }
  }
}

std::string ZkClient::get(const std::string& path) {
  char buf[64] = {0};
  int buf_len = sizeof(buf);
  int flag = zoo_get(_zhandle, path.c_str(), 0, buf, &buf_len, nullptr);
  if (flag != ZOK) {
    return "";
  } else {
    return buf;
  }
}

void ZkClient::sendHeartBeat() {
  std::thread thr([&]()->void{
      while (1) {
        int timegap = XmlConfig::getInstance().getTimeout() / 3;
        std::this_thread::sleep_for(std::chrono::milliseconds(timegap));
        zoo_exists(_zhandle, _rootNodePath.c_str(), 0, nullptr);
      }
  });
  thr.detach();
}

void ZkClient::setRootNodePath(const std::string& path) {
  _rootNodePath = path;
}

std::string ZkClient::getRootNodePath() {
  return _rootNodePath;
}

void ZkClient::watcher(zhandle_t* zh, int type, int state,
    const char* path, void* watcherCtx) {
  cout << "watcher type:" << type << endl;
  cout << "watcher state:" << state << endl;
  cout << "watcher path:" << path << endl;
  // session有关事件
  if (type == ZOO_SESSION_EVENT) {
    // session连接成功
    if (state == ZOO_CONNECTED_STATE) {
      // 通知等待线程连接成功
      sem_post(&_sem);
    } else if (state == ZOO_EXPIRED_SESSION_STATE) { // session超时
      cout << "timeout" << endl;
    }
  }
}
