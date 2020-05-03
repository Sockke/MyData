#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <algorithm>
using std::cerr;
using std::endl;

#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#define ROOT_PATH "../shared/"
#define UPLOAD_NAME "upload"

#define MIN_RANGE (10<<20)
#define MAX_RANGE (150<<20)

std::string getBoundary();
// 得到上传的文件名
std::string getFname(const std::string& header);

// 上传
bool upload(std::string& body, const std::string& fname, uint64_t offset, uint64_t size);
bool midupload(std::string& body, std::string& fname);
bool lastupload(std::string& body, std::string& fname);

#define MAX_LEN (100<<20)
#define LAST_LEN (200)

std::string boundary = getBoundary();

int main() {
  uint64_t content_length = atoll(getenv("Content-Length"));
  cerr << "content_length:" << content_length << endl;
  uint64_t need_read = 0;
  uint64_t maxlen = MAX_LEN;
  uint64_t has_read = 0;
  uint64_t last_len = LAST_LEN;
  bool islast = 0;
  std::string fname;
  while (has_read < content_length) {
    if (content_length - has_read > maxlen && content_length - has_read - maxlen < last_len) {
      need_read = content_length - has_read;
      islast = 1;
    } else if (content_length - has_read > maxlen) {
      need_read = maxlen;
    } else {
      need_read = content_length - has_read;
      islast = 1;
    }
    std::string bodyinfo(need_read, 0);
    if (islast == 0) { // 读取中间分块
      int ret = read(0, &bodyinfo[0], need_read);
      // 上传 
      if (midupload(bodyinfo, fname) == false) {
        std::cout << "failed" << endl;
        return -1;
      }
      //cerr << "bodyinfo[" << bodyinfo << "]" << endl;
      has_read += ret;
    } else {
      int ret = read(0, &bodyinfo[0], need_read); // 读取最后一个分块并保存
      if (lastupload(bodyinfo, fname) == false) {
        std::cout << "failed" << endl;
        return -1;
      }
      has_read += ret;
    }
  }
  std::cout << "ok" << endl;
  return 0;
}


// 得到boundary的值
std::string getBoundary() {
  std::string content_type = getenv("Content-Type");
  if (content_type.c_str() == nullptr) {
    return "";
  }
  std::string cur_name = "boundary=";
  size_t boundary_pos = content_type.find(cur_name);
  if (boundary_pos == std::string::npos) {
    return "";
  }
  boundary_pos += cur_name.size();
  return content_type.substr(boundary_pos);
}

// 得到上传的文件名
std::string getFname(const std::string& header) {
  std::string cur_name = " filename=\"";
  size_t pos = header.find(cur_name);
  if (pos == std::string::npos) {
    return "";
  }
  pos += cur_name.size();
  size_t next_pos = header.find("\"", pos);
  if (next_pos == std::string::npos) {
    return "";
  }
  return header.substr(pos, next_pos - pos);
}

// 上传文件
bool upload(std::string& body, const std::string& fname, uint64_t offset, uint64_t size) {
  std::ofstream ofs;
  ofs.open(ROOT_PATH+fname, std::ofstream::out | std::ofstream::binary | std::ofstream::app);
  if (!ofs.is_open()) {
    cerr <<  "file open error" << endl;
    return false;
  }
  ofs.write(&body[offset], size);
  if (!ofs.good()) {
    cerr << "file write error" << endl;
    return false;
  }
  return true;
}
bool midupload(std::string& body, std::string& fname) {
  // 两种情况
  // 1. 格式不完整, 但first_boundary完整
  std::string tail = "\r\n";
  std::string f_boundary = "--" + boundary + tail;
  size_t pos = body.find(f_boundary);
  if (pos != std::string::npos) {
    size_t next_pos = body.find(tail + tail);
    if (next_pos == std::string::npos) {
      return false;
    }
    fname = getFname(body.substr(pos, next_pos - pos));
    if (fname == "") {
      return false;
    }
    // pos指向数据的起始位置
    pos = next_pos + 2 * tail.size();
    if (upload(body, fname, pos, body.size() - pos) == false) {
      return false;
    }
  } else {
    // 2. 全是数据
    if (upload(body, fname, 0, body.size()) == false) {
      return false;
    }
  }
  return true;
}
bool lastupload(std::string& body, std::string& fname) {
  // 两种情况:
  // 1. 格式完整
  std::string tail = "\r\n";
  std::string f_boundary = "--" + boundary + tail;
  std::string l_boundary = tail + "--" + boundary + "--" + tail;
  size_t pos = body.find(f_boundary);
  if (pos != std::string::npos) {
    size_t next_pos = body.find(tail + tail);
    if (next_pos == std::string::npos) {
      return false;
    }
    fname = getFname(body.substr(pos, next_pos - pos));
    if (fname == "") {
      return false;
    }
    // pos指向数据的起始位置
    pos = next_pos + 2 * tail.size();
    // next_pos指向数据的结束位置
    next_pos = body.find(l_boundary);
    if (upload(body, fname, pos, next_pos - pos) == false) {
      return false;
    }
  } else {
    // 2. 格式不完整, 但是last_boundary完整
    size_t next_pos = body.find(l_boundary);
    if (next_pos == std::string::npos) {
      return false;
    }
    if (upload(body, fname, 0, next_pos) == false) {
      return false;
    }
  }
  return true;
}

