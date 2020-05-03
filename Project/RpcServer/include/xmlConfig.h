#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;

class XmlConfig {
  public:
    static XmlConfig& getInstance();
    std::string getIp() const;
    unsigned short getPort() const;
    std::string getZookeeperHost() const;
    int getTimeout() const;
  private:
    XmlConfig();
    XmlConfig(const XmlConfig&) = delete;
    XmlConfig& operator=(const XmlConfig&) = delete;

    std::string _ip;  // 服务端IP
    unsigned short _port; // 服务端端口
    std::string _zkhost; // zookeeper服务端ip与port
    int _timeout; // zookeeper连接超时时间
};
