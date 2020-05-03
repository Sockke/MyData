#include "../include/server.h"
#include <unistd.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <thread>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

const char* ROOT_PATH  = "../shared";
// 一次最大上传长度
const int MAX_LEN = (100<<20);
// 一次最小/最大下载范围            
//#define MIN_RANGE (4<<20)
const int MAX_RANGE = (150<<20);

/*
  请求与响应类
*/

bool Request::has_header(const std::string& key) {
    std::unordered_map<std::string, std::string>::iterator it = headers.find(key);    
    if (it == headers.end()) {    
      return false;    
    }    
    return true;    
}

std::string Request::get_header(const std::string& key) {
  return headers[key];
}

void Request::set_header(const std::string& key, const std::string& val) {
    headers[key] = val;    
}

bool Response::has_header(const std::string& key) {
  std::unordered_map<std::string, std::string>::iterator it = headers.find(key);
  if (it == headers.end()) {
    return false;
  }
  return true;
}

std::string Response::get_header(const std::string& key) {
  return headers[key];

}
void Response::set_header(const std::string& key, const std::string& val) {
  headers[key] = val;
}

/*
  Server类
*/

TcpSocket Server::_lsock;
Event Server::_event;

Server::Server(const std::string ip, short port) {
  _lsock.tsocket();
  _lsock.tbind(ip, port);
  _lsock.tlisten();
}

Server::~Server() {}

void Server::reg() {
  _event.add(_lsock.getSockfd(), accept_cb);
}

void Server::listen() {
  _event.wait();
}

void Server::accept_cb(int sockfd, short event, void* args) {
  if (event & EV_READ) {
    TcpSocket csock;
    if (_lsock.taccept(csock) == false) {
      usleep(3000);
      return;
    }
    _event.add(csock.getSockfd(), process_cb);
  }
}

/*
  Server端进行处理
*/

// 获取头部
bool get_header(TcpSocket& sock, std::string& headerinfo) {
  while (1) {
    std::string buf;
    // 试探接收, 观察是否有头部信息
    if (sock.trecvPeek(buf) == false) {
      return false;
    }
    size_t pos = buf.find("\r\n\r\n");
    if (pos == std::string::npos && buf.size() == 8192) {
      return false;
    } else if (pos != std::string::npos) {
      sock.trecv(headerinfo, pos + 4);
      return true;
    }
  }
}

// 发送响应    
std::string send_head(const Response& rsp) {    
  std::stringstream ss;    
  ss << "HTTP/1.1" << " " << rsp.status << " OK\r\n";    
  for (const auto& e : rsp.headers) {    
    ss << e.first << ": " << e.second << "\r\n";    
  }    
  ss << "\r\n";    
  return ss.str();    
}                    

// 解析头部
bool parse_header(const std::string& headerinfo, Request& req) {
  std::vector<std::string> headerlist;
  boost::split(headerlist, headerinfo, boost::is_any_of("\r\n"), \
      boost::token_compress_on);
  // 首行解析
  std::string firstline = headerlist[0];
  std::vector<std::string> firstlist;
  boost::split(firstlist, firstline, boost::is_any_of(" "), \
      boost::token_compress_on);
  req.method = firstlist[0];
  std::string url = firstlist[1];
  size_t path_pos = url.find("?");
  if (path_pos == std::string::npos) {
    req.path = url;
  } else {
    req.path = url.substr(0, path_pos);
    std::vector<std::string> querylist;
    std::string query = url.substr(path_pos + 1);
    boost::split(querylist, query, boost::is_any_of("&"), \
        boost::token_compress_on);
    for (auto& e : querylist) {
      size_t params_pos = e.find("=");
      req.query[e.substr(0, params_pos)]  = e.substr(params_pos + 1);
    }
  }
  // 头部解析
  for (size_t i = 1; i < headerlist.size() - 1; ++i) {
    size_t params_pos = headerlist[i].find(": ");
    req.set_header(headerlist[i].substr(0, params_pos), headerlist[i].substr(params_pos + 2));
  }
  return true;
}

/*
  文件上传
*/
bool response_upload(TcpSocket& sock, Request& req, Response& rsp) {
    // 父进程从pipe_p[0]里面读, pipe_c[1]里面写
  std::string realpath = "." + req.path;
  int pipe_p[2], pipe_c[2];
  if (pipe(pipe_p) < 0) {
    perror("pipe create error");
    return false;
  }
  if (pipe(pipe_c) < 0) {
    perror("pipe create error");
    close(pipe_p[0]);
    close(pipe_p[1]);
    return false;
  }
  int pid = fork();
  if (pid < 0) {
    perror("fork error");
    for (int i = 0; i < 2; ++i) {
      close(pipe_p[i]);
      close(pipe_c[i]);
    }
    return false;
  } else if (pid == 0) {
    // 关闭子进程不用的管道描述符
    close(pipe_p[0]);
    close(pipe_c[1]);
    // 重定向保存子进程的管道描述符
    dup2(pipe_c[0], 0);
    dup2(pipe_p[1], 1);
    // 进程替换之前, 将请求头信息设置到环境变量中
    setenv("REQ_METHOD", req.method.c_str(), 1);
    setenv("REQ_PATH", req.path.c_str(), 1);
    for (const auto& e : req.headers) {
      setenv(e.first.c_str(), e.second.c_str(), 1);
    }
    // 进程替换
    execl(realpath.c_str(), realpath.c_str(), nullptr);
  } 
  // 父进程关闭不用的管道描述符
  close(pipe_p[1]);
  close(pipe_c[0]);
  // 父进程通过管道将请求正文传递给子进程
  std::string content_length = req.get_header("Content-Length");
  if (content_length == "") {
    //perror("no content_length");
    return false;
  }
  uint64_t all_len= atoll(content_length.c_str()); // 需要发的总长度
  uint64_t need_recv = 0; // 每次需要接收的长度
  uint64_t has_recv = 0; // 已经接收的长度
  uint64_t max_recv = MAX_LEN; // 每次最大的接收长度
  while (has_recv < all_len) {
    if (all_len - has_recv > max_recv) { // 限制接收
      need_recv = max_recv;
    } else {
      need_recv = all_len - has_recv;
    }
    std::string bodyinfo;
    // 接收请求的部分body
    bool rret = sock.trecv(bodyinfo, need_recv);
    if (rret == false) {
      return false;
    }
    // 将接收的部分body交给外部进程处理
    int wret = write(pipe_c[1], bodyinfo.c_str(), need_recv);
    if (wret < 0) {
      //perror("write error");
      return false;
    } else if (wret == 0) {
      break;
    }
    has_recv += wret;
  }
  // 父进程通过管道接收子进程传递的处理结果
  rsp.status = 200;
  sock.tsend(send_head(rsp));
  while (1) {
    char buf[1024] = {0};
    int ret = read(pipe_p[0], buf, 1023);
    if (ret < 0) {
      return false;
    }
    if (ret == 0) {
      break;
    }
    rsp.body += buf;
    sock.tsend(rsp.body);
  }
  return true;            
}

/*
   展示文件列表
   */
bool response_showlist(TcpSocket& sock, Request& req, Response& rsp) {
  std::stringstream ss;
  std::string realpath = ROOT_PATH + req.path; 
  ss << "<html>";
  ss << "<head>";
  ss << "<style>";
  ss << "@import url('https://fonts.googleapis.com/css?family=Poppins:300,400,500,600,700,800&display=swap');";
  ss << "*{";
  ss << "margin: 0;";
  ss << "padding: 0;";
  ss << "box-sizing: border-box;";
  ss << "font-family: 'Poppins', sans-serif;";
  ss << "}";

  ss << ".upload_mg {";
  ss << "width: 100%;";
  ss << "height: 180px;";
  ss << "display: flex;";
  ss << "justify-content: center;";
  ss << "background: gray;";
  ss << "background-repeat: no-repeat;";
  ss << "}";

  ss << ".upload_mg .upload_pd {";
  ss << "width: 70%;";
  ss << "height: 100%;";
  ss << "display: flex;";
  ss << "justify-content: center;";
  ss << "}";

  ss << ".upload_mg .upload_pd:hover {";
  ss << "filter: drop-shadow(5px 5px 10px black);";
  ss << "transform: scale(1.1);";
  ss << "}";

  ss << ".upload_mg .upload_pd .upload_content {";
  ss << "width: 50%;";
  ss << "height: 100%;";
  ss << "text-align: center;";
  ss << "}";

  ss << ".upload_mg .upload_pd .upload_content p{";
  ss << "display: inline-block;";
  ss << "margin-top: 15px;";
  ss << "padding: 5px 10px;";
  ss << "background: #262626;";
  ss << "color: #fff;";
  ss << "}";

  ss << ".file_mg {";
  ss <<"margin: auto;";
  ss <<"max-width: 1100px;";
  ss <<"position: relative;";
  ss <<"display: flex;";
  ss <<"justify-content: center;";
  ss <<"flex-wrap: wrap;";
  ss <<"transition: 0.5s;";
  ss <<"background: url('./5.jpg') 0px 0px;";
  ss <<"}";

  ss << ".file_mg .file_pd {";
  ss << "position: relative;";
  ss << "width: 350px;";
  ss << "height: 200px;";
  ss << "background: #fff;";
  ss << "display: flex;";
  ss << "justify-content: center;";
  ss << "align-items: center;";
  ss << "transition: 0.5s;";
  ss << "}";

  ss << ".file_mg .file_pd:hover {";
  ss << "filter: blur(0px);";
  ss << "transform: scale(1);";
  ss << "}";

  ss << ".file_mg .file_pd:before {";
  ss << "content: '';";
  ss << "position: absolute;";
  ss << "width: 100%;";
  ss << "height: 100%;";
  ss << "background: #fff;";
  ss << "z-index: 1;";
  ss << "transition: 0.5s;";
  ss << "}";

  ss << ".file_mg .file_pd:hover:before {";
  ss << "background: #000;";
  ss << "transform: scaleX(1.50);";
  ss << "box-shadow: 0 5px 15px rgba(0,0,0,.2);";
  ss << "}";

  ss << ".file_mg .file_pd .file_content {";
  ss << "text-align: center;";
  ss << "z-index: 2;";
  ss << "padding: 0 20px;";
  ss << "transition: 0.5s;";
  ss << "}";

  ss << ".file_mg .file_pd:hover .file_content {";/*光标碰触后变色*/
  ss << "  color: #fff;";
  ss << "}";

  ss << ".file_mg .file_pd .file_content h2{ ";
  ss << "  font-size: 2em;";
  ss << " }";

  ss << ".file_mg .file_pd .file_content p{ ";
  ss << "  font-size: 0.9em;";
  ss << " }";

  ss << ".file_mg .file_pd .file_content a{ ";
  ss << "  display: inline-block;";
  ss << "  margin-top: 15px;";
  ss << "  padding: 5px 10px;";
  ss << "  background: #262626;";
  ss << "  color: #fff;";
  ss << "  text-decoration: none;";
  ss << " }";                          
  ss << ".file_mg .file_pd:hover .file_content a{ ";
  ss << "  background: #2196f3;";
  ss << " }";

  ss << ".end {";
  ss << "width: 100%;";
  ss << "height: 50px;";
  ss << "background: black;";
  ss << "position: relative;";
  ss << "display: flex;";
  ss << "justify-content: center;";
  ss << "flex-wrap: wrap;";
  ss << "transition: 0.5s;";
  ss << "}";

  ss << ".end h2 {";
  ss << "text-align: center;";
  ss << "color: white;";
  ss << "}";

  ss << "</style>";
  ss << "<title>forShare</title>";
  //ss << "<link rel='stylesheet' type='text/css' href='./test.css'>";
  ss << "</head>";
  ss << "<body>";
  ss << "<div class='upload_mg'>";
  ss << "<div class='upload_pd'>";
  ss << "<div class='upload_content'>";
  ss << "<h1>ForShare</h1>";
  ss << "<form action='/upload' method='post' enctype='multipart/form-data'>";
  ss << "<p>UPLOAD</p>";
  ss << "<p><input type='file' name='upload'></p>";
  ss << "<p><input type='submit'></p>";
  ss << "</form>";
  ss << "</div></div></div>";

  boost::filesystem::directory_iterator begin(realpath);
  boost::filesystem::directory_iterator end;
  while (begin != end) {
    // 确定每个文件的uri
    std::string fname = begin->path().filename().string();
    std::string url_root = ROOT_PATH;
    std::string uri_root = realpath.substr(url_root.size());
    std::string uri = uri_root + fname;
    ss << "<div class='file_mg'>";
    ss << "<div class='file_pd'>";
    ss << "<div class='file_content'>";
    // 目录文件
    if (boost::filesystem::is_directory(begin->path())) {
      ss << "<h2>" << fname << "/</h2>";
      ss << "<a href='" << uri << "/'>"  << "OPEN" << "</a>";
    } else { // 普通文件
      ss << "<h2>" << fname << "</h2>";
      ss << "<a href='" << uri << "'>"  << "DOWNLOAD" << "</a>";
    }
    ss << "</div></div></div>";
    ++begin;
  }
  ss << "<div class='end'>";
  ss << "<h2>END<h2>";
  ss << "</div>";
  ss << "</body>";
  ss << "</html>";
  // 响应指定信息
  rsp.status = 200;
  rsp.set_header("Content-Type", "text/html");
  rsp.set_header("Content-Length", std::to_string(ss.str().size()));
  sock.tsend(send_head(rsp));
  rsp.body = ss.str();
  sock.tsend(rsp.body);
  return true;                   
}

/*
  文件下载
*/

bool download(TcpSocket& sock, const std::string& fpath, \
    int64_t start, int64_t len) {
  int64_t offset_end = start + len - 1;
  int64_t range_each = len;
  if (range_each > MAX_RANGE) {
    range_each = MAX_RANGE;
  }
  int nums = 0;
  if (range_each != 0) {
    nums = (len + range_each - 1) / range_each;
  } 
  while (nums--) {
    uint64_t end = start + std::min(range_each, offset_end - start + 1) - 1;
    std::ifstream ifs;
    ifs.open(fpath, std::ifstream::in | std::ifstream::binary);
    if (!ifs.is_open()) {
      return false;
    }
    ifs.seekg(start, std::ifstream::beg);
    size_t cursize = end - start + 1;
    std::string body_each(cursize, 0);
    ifs.read(&body_each[0], cursize);
    if (!ifs.good()) {
      return false;
    }
    // 发送响应body
    sock.tsend(body_each);
    start = end + 1;
  }
  return true;
}

bool response_download(TcpSocket& sock, Request& req, Response& rsp) {
  std::string realpath = ROOT_PATH + req.path;
  int64_t fsize = boost::filesystem::file_size(realpath);
  rsp.status = 206;
  rsp.set_header("Content-Type", "application/octet-stream");
  rsp.set_header("Accept-Ranges", "bytes");
  int64_t last_m_time = boost::filesystem::last_write_time(realpath);
  std::string etag = std::to_string(fsize) + std::to_string(last_m_time);
  rsp.set_header("ETag", etag);
  sock.tsend(send_head(rsp));
  bool has_range = req.has_header("Range");
  if (has_range  == false) { // 正常下载
    if (download(sock, realpath, 0, fsize) == false) {
      return false;
    }
  } else { // 断点续传
    // Range: bytes=start-end
    std::string range_val = req.get_header("Range");
    std::string begin_before = "bytes=";
    size_t pos = range_val.find(begin_before);
    if (pos == std::string::npos) {
      return false;
    }
    pos += begin_before.size();
    size_t next_pos = range_val.find("-", pos);
    if (next_pos == std::string::npos) {
      return false;
    }
    std::string begin_str = range_val.substr(pos, next_pos - pos);
    int64_t begin = atoll(begin_str.c_str());
    pos = next_pos + 1;
    std::string end_str = range_val.substr(pos);
    int64_t end;
    if (end_str.empty()) {
      end = fsize - 1;
    } else {
      end = atoll(end_str.c_str());
    }
    if (download(sock, realpath, begin, end - begin + 1) == false) {
      return false;
    }
  } 
  return true;
}

/*
  响应列表
*/

void write_response(TcpSocket& sock, Request& req, Response& rsp) {
  // 判断请求的uri是否存在
  if ((req.method == "GET" && !req.query.empty())
      || req.method == "POST") { // 多进程处理
    std::string realpath = "../bin" + req.path;
    if (!boost::filesystem::exists(realpath)) {
      rsp.status = 404;
      sock.tsend(send_head(rsp));
      return;
    }
    cout << "in upload" << endl;
    if (response_upload(sock, req, rsp) == false) {
      rsp.status = 500;
      sock.tsend(send_head(rsp));
      return;
    }
  } else { // (文件列表展示+文件下载)
    // 判断请求的uri是否存在
    std::string realpath = ROOT_PATH + req.path; 
    if (!boost::filesystem::exists(realpath)) {
      rsp.status = 404;
      sock.tsend(send_head(rsp));
      return;
    }
    if (boost::filesystem::is_directory(realpath)) {
      // 文件列表展示
      if (response_showlist(sock, req, rsp) == false) {
        rsp.status = 400;
        sock.tsend(send_head(rsp));
        return;
      }
    } else {
      cout << "in download" << endl;
      // 文件下载
      if (response_download(sock, req, rsp) == false) {
        rsp.status = 500;
        sock.tsend(send_head(rsp));
        return;
      }
    }
  }
}

void Server::process_cb(int sockfd, short event, void* args) {
  if (event & EV_READ) {
    std::thread t([&]()->void{
        TcpSocket csock;     
        csock.setSockfd(sockfd);
        Request req;
        Response rsp;
        std::string header_info;
        // 获取并解析头部信息
        if (get_header(csock, header_info) == false) {    
        rsp.status = 400;    
        csock.tsend(send_head(rsp));    
        return;    
        }    
        if (parse_header(header_info, req) == false) {    
        rsp.status = 400;    
        csock.tsend(send_head(rsp));    
        return;    
        }    
        // 根据请求头信息建立指定的响应
        write_response(csock, req, rsp);
        // 发送响应信息
        //sock.Send(send_response(rsp));
        close(csock.getSockfd());
    });
    t.detach();
  }
}



