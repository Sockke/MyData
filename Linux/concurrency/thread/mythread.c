#include <stdio.h>
#include <pthread.h>
/*
  [线程底层]:
  其实是通过clone来指定共享资源的方式, 来模拟的线程
  clone_flag, 如果指定了CLONE_VM, 那么就称为线程,
  如果仅制定了CLONE_FS, CLONE_FILES, 那么就称为进程
  
  [系统线程调用接口]:
  1. 定义线程句柄:
  pthread_t thr;
  2. 启动线程:
  pthread_create(&thr, NULL, thr_start, (void*)args);
  线程入口函数:
  void* thr_start(void* args);
  3. 设置线程回收方式:
  pthread_join(thr, NULL);
  pthread_detach(thr, NULL);
  4. 线程的终止
  pthread_cancel(thr)  // 取消另一个线程
  pthread_exit(NULL)  // 终止当前线程
*/
void* thr_start(void* args) {
  const char* say = (const char*)args;
  printf("%lu say:%s\n", pthread_self(), say);
  return NULL;
}
int main() {
  const char* say = "hello world";
  pthread_t thr;
  pthread_create(&thr, NULL, thr_start, (void*)say);
  pthread_join(thr, NULL);
  return 0;
}
