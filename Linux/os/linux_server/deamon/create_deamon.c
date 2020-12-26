#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bool create_deamon() {
  pid_t pid = fork(); 
  if (pid < 0) {
    return -1;
  } else if (pid > 0) {
    // 父进程退出
    exit(1);
  } else {
    // 创建新的会话
    pid_t sid = setsid();
    if (sid < 0) {
      return false;    
    }

    // 切换工作目录
    if (chdir("/") < 0) {
      return false;
    }

    // 关闭输入输出设备, 打开的文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    // close 已经打开的文件描述符 ... 
    
    // 将输入输出定向到/dev/null文件
    umask(0); // open的文件权限为0777
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    return true;
  }
}

int main() {
  return 0;
}
