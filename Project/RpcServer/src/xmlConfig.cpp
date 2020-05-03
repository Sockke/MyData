#include "../include/xmlConfig.h"
#include "../third_party/tinyxml/tinyxml.h"

XmlConfig::XmlConfig() {
  TiXmlDocument lconfigXML;
  if (!lconfigXML.LoadFile("../config/rpc_cfg.xml")) {
    cout << "load zookeeper configure error..." << endl;
    exit(EXIT_FAILURE);
  }
  // 加载服务端的ip与port信息
  const TiXmlNode* node = lconfigXML.RootElement()->IterateChildren("RpcServer", nullptr);
  const TiXmlNode* cnode = nullptr;
  if (node == nullptr) {
    cout << "no effective service of your configure..." << endl;
    exit(EXIT_FAILURE);
  } else {
    cnode = node->IterateChildren("ip", nullptr);
    _ip = cnode->ToElement()->GetText();
    cnode = node->IterateChildren("port", nullptr);
    _port = atoi(cnode->ToElement()->GetText());
  }
  // 加载zookeeper服务端的ip与port信息
  node = lconfigXML.RootElement()->IterateChildren("zookeeper", nullptr);
  if (node == nullptr) {
    cout << "no zookeeper info of your configure..." << endl;
    exit(EXIT_FAILURE);
  } else {
    cnode = node->IterateChildren("host", nullptr);
    _zkhost = cnode->ToElement()->GetText(); 
    cnode = node->IterateChildren("timeout", nullptr);
    _timeout = atoi(cnode->ToElement()->GetText()); 
  }
  cout << "load configure success..." << endl;
}

XmlConfig& XmlConfig::getInstance() {
  static XmlConfig xml;
  return xml;
}

std::string XmlConfig::getIp() const {
  return _ip;
}

unsigned short XmlConfig::getPort() const {
  return _port;
}

std::string XmlConfig::getZookeeperHost() const {
  return _zkhost;
}

int XmlConfig::getTimeout() const {
  return _timeout;
}
