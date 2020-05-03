#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

/*
  守护进程: 不依赖于终端, 独立于后台运行的进程

  创建守护进程, 要保证不依赖于终端, 在后台运行
  1. fork创建子进程, 然后父进程退出
  必须要让子进程来成为守护进程, 因为成为守护进程之前必须要调用setid生成新会话,
  调用setsid的进程必须不是进程组组长
  2. setsid创建新会话, 因为要脱离终端所在的会话, 生成新会话
  此时该进程成为新会话的首进程
  3. chdir("/"), 改变守护进程的工作目录为根目录
  由于子进程继承父进程的工作目录, 工作目录可能会被删除
  4. umask(0), 将文件掩码置0
  子进程继承父进程的文件掩码, 可能会影响创建文件的操作权限
  5. close(fd), 关闭不需要的文件描述符
  子进程拷贝父进程的文件描述符表, 会浪费系统的资源
*/

int main() {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork erro");
    return -1;
  } else if (pid > 0) {
    exit(0); //1
  } else {
    setsid(); //2
    chdir("/"); //3
    umask(0); //4
    int fd_size = getdtablesize();
    int i;
    for (i = 0; i < fd_size; ++i) {
      close(i); //5
    }
  }

  while (1) {
    FILE* fp = fopen("/tmp/sock.log", "a");
    if (fp == NULL) {
      exit(0);
    }
    time_t tv;
    time(&tv);
    fprintf(fp, "time is %s\n", asctime(localtime(&tv)));
    fclose(fp);
    sleep(5);
  }
  return 0;
}
