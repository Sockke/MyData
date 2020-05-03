#pragma once
#include "tcpsocket.h"
#include "myevent.h"

using std::cout;
using std::endl;

struct Request {
  std::string method; // 请求方法    
  std::string path; // 请求资源路径    
  std::unordered_map<std::string, std::string> query; // 请求查询字符串    
  std::unordered_map<std::string, std::string> headers; // 请求头部    
  std::string body; // 请求正文    

  bool has_header(const std::string& key);
  std::string get_header(const std::string& key);
  void set_header(const std::string& key, const std::string& val);
};

struct Response {
  int status; // 响应状态码
  std::unordered_map<std::string, std::string> headers; // 响应头部
  std::string body; // 响应正文
  bool has_header(const std::string& key);
  std::string get_header(const std::string& key);
  void set_header(const std::string& key, const std::string& val);
};

class Server {
  public:
    Server(const std::string ip, short port);
    ~Server();
    void listen();
    void reg();
  private:
    static void accept_cb(int sockfd, short event, void* args);
    static void process_cb(int sockfd, short event, void* args);
    static TcpSocket _lsock; 
    static Event _event;
};
