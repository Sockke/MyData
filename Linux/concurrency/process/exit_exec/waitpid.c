#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

/*
  问什么要等待子进程退出?
  1. 等待子进程退出的目的是正常回收子进程的资源, 防止产生僵死进程.
  因为当子进程的资源是需要父进程来进行回收的, 如果父进程不等待子进程的退出,
  子进程的资源就无法正常得到释放, 成为僵死进程, 导致内存泄漏.

  如何解决僵死进程?
  1. 产生的僵死进程, 可以通过kill -9进行强杀
  2. 但是在开发过程中, 尽量是防止产生僵死进程, 而不是解决僵死进程.
  父进程要等待子进程的退出, 正常回收子进程的资源

  孤儿进程?
  孤儿进程是由于父进程先于子进程退出, 子进程资源无法正常得到回收.
  1. 无论是僵死进程还是孤儿进程, 都是由于子进程的资源无法正常得到释放导致的.
  如果产生孤儿进程, 系统会调用寻父算法, 将孤儿进程进行领养,
  一般会交给1号进程init进程来进行领养回收子进程资源

  waitpid(-1, NULL, 0), 阻塞等待任意子进程退出, 
  与wait(NULL)功能相同
  waitpid(-1, NULL, WNOHANG), 非阻塞等待子进程退出
  如果返回值为0, 说明没有子进程退出, 可以干其他的事
*/

//void wait_all() {
//  pid_t pids[2];
//  int i;
//  for (i = 0; i < 2; ++i) {
//    pids[i] = fork();
//    if (pids[i] < 0) {
//      perror("fork error");
//      exit(-1);
//    }
//    // 子进程
//    if (pids[i] == 0) {
//      printf("child: %d\n", getpid());
//      exit(i);
//    }
//  }
//  pid_t retpid = 0;
//  int status = 0;
//  while ((retpid = waitpid(-1, &status, 0)) > 0) {
//    if (WIFEXITED(status)) {
//      printf("child %d exit successfully: %d\n", retpid, WEXITSTATUS(status));
//    } else {
//      printf("child %d exit failed\n", retpid);
//    }
//  }
//}

void wait_all() {
  pid_t pids[2];
  int i;
  for (i = 0; i < 2; ++i) {
    pids[i] = fork();
    if (pids[i] < 0) {
      perror("fork error");
      exit(-1);
    }
    if (pids[i] == 0) {
      printf("chlid: %d\n", getpid());
      sleep(1);
      exit(i);
    }
  }
  while (i--) {
    while (waitpid(pids[i], NULL, WNOHANG) == 0) {
      usleep(200000);
      printf("smoking\n");
    }
  }
}

int main() {
  wait_all();
  return 0;
}
