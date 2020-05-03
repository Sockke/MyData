#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

/*
  生产者消费者模型
  生产者与消费者要解决的3个问题:
  1. 生产者与消费者操作同一块缓冲区, 需要保证互斥
  2. 当缓冲区满时, 生产者不能再生产了
  3. 当缓冲区空时, 消费者不能再消费了

  保证线程同步有2种比较常见的操作:
  1. 条件变量搭配互斥锁
  2. 信号量
*/

#define PRODUCER 3
#define CONSUMER 2
#define N 10 // 缓冲区大小

int buf[N]; // 缓冲区
int* in = buf;
int* out = buf;
int data = 0;
sem_t sem_p, sem_c, sem_mtx;

void* produce(void* args) {
  while (1) {
    sem_wait(&sem_p);
    sem_wait(&sem_mtx);
    ++data;
    *in = data;
    in = in + (in - buf + 1) % N;
    printf("%lu号生产者生产了数据:%d\n", pthread_self(), data);
    sem_post(&sem_mtx);
    sleep(1);
    sem_post(&sem_c);
  }
  return args;
}

void* consume(void* args) {
  while (1) {
    sem_wait(&sem_c);
    sem_wait(&sem_mtx);
    printf("%lu号消费者消费了数据:%d\n", pthread_self(), *out);
    --data;
    out = out + (out - buf + 1) % N;
    sem_post(&sem_mtx);
    sleep(1);
    sem_post(&sem_p);
  }
  return args;
}

int main() {
  sem_init(&sem_p, 0, N); // 生产者初始可以生产N个
  sem_init(&sem_c, 0, 0); // 消费者初始可以消费0个
  sem_init(&sem_mtx, 0, 1); // 实现锁
  pthread_t producers[PRODUCER];
  pthread_t consumers[CONSUMER];
  int i;
  for (i = 0; i < PRODUCER; ++i) {
    pthread_create(&producers[i], NULL, produce, NULL);
  }
  for (i = 0; i < CONSUMER; ++i) {
    pthread_create(&consumers[i], NULL, consume, NULL);
  }
  for (i = 0; i < PRODUCER; ++i) {
    pthread_join(producers[i], NULL);
  }
  for (i = 0; i < CONSUMER; ++i) {
    pthread_join(consumers[i], NULL);
  }
  sem_destroy(&sem_p);
  sem_destroy(&sem_c);
  sem_destroy(&sem_mtx);
  return 0;
}
