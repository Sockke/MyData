#include "connection_pool.h"
#include <fstream>
#include <functional>
#include <memory>
#include <chrono>

#define CFG_FILE "connectionPool.cfg"


ConnectionPool* ConnectionPool::getPool() {
  static ConnectionPool connPool;
  return &connPool;
}

ConnectionPool::ConnectionPool() {
  if (!loadCfgFile()) {
    cout << "load config file error" << endl;
    return;
  }
  // 创建初始数量的连接
  _initConnSize = atoi(_connMap["initConnSize"].c_str());
  _maxConnSize = atoi(_connMap["maxConnSize"].c_str());
  _maxConnIdleTime = atoi(_connMap["maxConnIdleTime"].c_str());
  _maxConnTimeout = atoi(_connMap["maxConnTimeout"].c_str());
  std::string ip = _connMap["ip"];
  std::string username = _connMap["username"];
  std::string passwd = _connMap["passwd"];
  std::string database = _connMap["database"];
  int port = atoi(_connMap["port"].c_str());
  for (int i = 0; i < _initConnSize; ++i) {
    Connection* conn = new Connection();
    conn->connect(ip, username, passwd, database, port);
    conn->setStartTime();
    _connQueue.push(conn);
    ++_curConnSize;
  }
  // 启动生产连接线程
  std::thread produce(std::bind(&ConnectionPool::produceConn, this));
  produce.detach();
  // 启动空闲连接空闲时间扫描线程
  std::thread scanner(std::bind(&ConnectionPool::scannIdleConn, this));
  scanner.detach();
}

ConnectionPool::~ConnectionPool() {

}
bool ConnectionPool::loadCfgFile() {
  std::ifstream ifs; 
  ifs.open(CFG_FILE);
  if (!ifs.is_open()) {
    cout << "file open error" << endl;
    return false;
  }
  while (!ifs.eof()) {
    std::string data;
    std::getline(ifs, data);
    size_t pos = data.find("=");
    if (pos == std::string::npos) {
      continue;
    }
    std::string key = data.substr(0, pos);
    std::string val = data.substr(pos + 1, data.size() - pos - 1); // 不包括'\n'
    _connMap[key] = val;
  }
  return true;
}

// 生产连接
void ConnectionPool::produceConn() {
  while (1) {
    std::unique_lock<std::mutex> ulock(_mtx);
    // 空闲连接队列不为空, 等待消费者消费连接
    while (!_connQueue.empty()) {
      _conv.wait(ulock);
    }
    // 空闲队列为空, 生产者生产连接
    if (_curConnSize < _maxConnSize) {
      std::string ip = _connMap["ip"];
      std::string username = _connMap["username"];
      std::string passwd = _connMap["passwd"];
      std::string database = _connMap["database"];
      int port = atoi(_connMap["port"].c_str());
      Connection* conn = new Connection();
      conn->connect(ip, username, passwd, database, port);
      conn->setStartTime();
      _connQueue.push(conn);
      ++_curConnSize;
    }
    // 生产完毕, 通知消费者消费连接
    _conv.notify_all();
  }
}

// 消费连接
std::shared_ptr<Connection> ConnectionPool::getConn() {
  std::unique_lock<std::mutex> ulock(_mtx);
  // 空闲连接队列为空, 等待生产者生产连接
  while (_connQueue.empty()) {
    // 等待超时, 并且空闲连接队列仍为空, 则代表请求连接超时
    if (_conv.wait_for(ulock, std::chrono::milliseconds(_maxConnTimeout)) 
        == std::cv_status::timeout) {
      if (_connQueue.empty()) {
        cout << "obtain connection timeout" << endl;
        return nullptr;
      }
    }
  }
  // 获取连接, 自定义删除器, 使得使用完的连接重新方法空闲队列当中
  std::shared_ptr<Connection> conn(_connQueue.front(), [&](Connection* conn)->void{
    std::unique_lock<std::mutex> ulock(_mtx);
    conn->setStartTime();
    _connQueue.push(conn);
  });
  _connQueue.pop();
  // 唤醒生产者, 生产连接
  _conv.notify_all();
  return conn;
}

// 扫描空闲连接的空闲时间的线程函数
void ConnectionPool::scannIdleConn() {
  std::this_thread::sleep_for(std::chrono::seconds(_maxConnIdleTime));
  std::unique_lock<std::mutex> ulock(_mtx);
  while (_curConnSize > _initConnSize) {
    Connection* conn = _connQueue.front();
    // 空闲时间超时
    if (conn->getAliveTime()/CLOCKS_PER_SEC >= _maxConnIdleTime) {
      _connQueue.pop();
      --_curConnSize;
      delete conn;
    } else {
      break;
    }
  }
}
