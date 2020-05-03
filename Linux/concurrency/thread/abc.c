#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sems[3];
const char* info[] = {"a","b","c"};
void* thr_start(void* args) {
  int i = *(int*)args;
  while (1) {
    sem_wait(&sems[i]); // 计数器-1
    printf("%s\n", info[i]);
    sleep(1);
    sem_post(&sems[(i+1) % 3]); // 计数器+1, 唤醒下一个
  }
  return NULL;
}
int main() {
  sem_init(&sems[0], 0, 1);
  sem_init(&sems[1], 0, 0);
  sem_init(&sems[2], 0, 0);
  int i;
  pthread_t thrs[3];
  for (i = 0; i < 3; ++i) {
    pthread_create(&thrs[i], NULL, thr_start, (void*)&i);
  }
  for (i = 0; i < 3; ++i) {
    pthread_join(thrs[i], NULL);
  }
  return 0;
}
