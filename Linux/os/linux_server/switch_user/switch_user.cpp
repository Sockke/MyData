#include <iostream>
#include <unistd.h>
#include <wait.h>
#include <cstring>
#include <memory>
#include <functional>
using namespace std;

const char* USERINFONAME = "passwd_info.txt";

// 用户切换
bool switchToUser(uid_t dest_uid, uid_t dest_gid) {
  uid_t cur_uid = getuid();
  uid_t cur_gid = getgid();
  // 当前不是root, 也不是目标用户
  if ((cur_uid != 0 || cur_gid != 0) && (cur_uid != dest_uid || cur_gid != dest_gid)) {
    // 输密码
    return false;
  }
  // 目标用户
  if (cur_uid != 0) {
    return true;
  }
  // root用户, 直接切换
  if ((setuid(dest_uid) < 0) || (setgid(dest_gid) < 0)) {
    return false;
  }
  return true;
}

bool getUidAndGid(const string& info, const string& user, uid_t* uid, uid_t* gid) {
  unique_ptr<FILE, function<void(FILE*)>> up_fp(fopen(info.c_str(), "r"), [](FILE* fp)->void{
    fclose(fp);
  });
  char buf[1024];
  memset(buf, 0x00, 1024);
  while (fgets(buf, 1023, up_fp.get()) != nullptr) {
    string s(buf);
    size_t pos = s.find(" ", 0);
    if (pos == string::npos) {
      return false;
    }
    string username = s.substr(0, pos);
    if (username == user) {
      size_t new_pos = s.find(" ", pos + 1);
      if (new_pos == string::npos) {
        return false;
      }
      *uid = atoi(s.substr(pos+1, new_pos-pos-1).c_str());
      *gid = atoi(s.substr(new_pos+1).c_str());
      break;
    }
    memset(buf, 0x00, 1024);
  }
  return true;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "./a.out username" << endl;
    return -1;
  }
  pid_t pid = fork();
  if (pid < 0) {
    return -1;
  }
  if (pid == 0) {
    // 子进程 
    if (execlp("./read_passwd.sh", "./read_passwd.sh")) {
      exit(-1);
    }
  } 
  // 父进程
  wait(nullptr);
  // 取uid和gid
  uid_t dest_uid = 0, dest_gid = 0;
  if (!getUidAndGid(USERINFONAME, argv[1], &dest_uid, &dest_gid)) {
    perror("get uid and gid failed");
    return -1;
  }
  if (switchToUser(dest_uid, dest_gid)) {
    cout << "switch to " << argv[1] << " successfully" << endl;
  } else {
    cout << "switch to " << argv[1] << " failed" << endl;
  }
  return 0;
}
