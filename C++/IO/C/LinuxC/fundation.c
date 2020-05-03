#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

// Linux下对文件的读写操作
//
// 如何判断文件的结尾
// 1. Linux系统接口中没有类似与feof的函数
// Linux系统接口操作的是二进制, 因此不能通过EOF来判断文件的结束
// 2. 通过判断读函数返回值来判断文件的结束, 
// 如果返回值符合预期则操作, 否则结束循环
//
// open中的权限 & ~mask = 文件操作权限

typedef struct Info {
  char _name[30];
  int _age;
  struct Info* _next;
}Info;
typedef struct AllInfo {
  Info* _infos;
}AllInfo;

void initInfos(AllInfo* infos) {
  assert(infos != NULL);
  infos->_infos = (Info*)malloc(sizeof(Info));
  if (infos->_infos == NULL) {
    perror("bad alloc");
    exit(-1);
  }
  infos->_infos->_next = NULL;
}
void push_front(AllInfo* infos, const char* name, int age) {
  assert(infos != NULL);
  Info* info = (Info*)malloc(sizeof(Info));
  if (info == NULL) {
    perror("bad alloc");
    exit(-1);
  }
  strcpy(info->_name, name);
  info->_age = age;
  info->_next = infos->_infos->_next;
  infos->_infos->_next = info;
}

void writeFile(const char* filename, AllInfo* infos) {
  assert(filename != NULL && infos != NULL);
  int fd = open(filename, O_CREAT | O_WRONLY, 0664);
  if (fd < 0) {
    perror("file open error");
    exit(-1);
  }
  Info* cur = infos->_infos->_next;
  while (cur != NULL) {
    write(fd, (char*)cur, sizeof(struct Info));
    cur = cur->_next;
  }
  close(fd);
}

void readFile(const char* filename, AllInfo* infos) {
  assert(filename != NULL && infos != NULL);
  int fd = open(filename, O_RDONLY, 0664);
  if (fd < 0) {
    perror("file open error");
    exit(-1);
  }
  while (1) {
    Info info;
    int ret = read(fd, (char*)&info, sizeof(struct Info));
    if (ret == sizeof(struct Info)) {
      push_front(infos, info._name, info._age);
    } else {
      break;
    }
  }
  close(fd);
}

void show(AllInfo* infos) {
  assert(infos != NULL);
  Info* cur = infos->_infos->_next;
  while (cur != NULL) {
    printf("%s:%d\n", cur->_name, cur->_age);
    cur = cur->_next;
  }
}

int main() {
  AllInfo infos;
  initInfos(&infos);
  //push_front(&infos, "sock", 19);
  //push_front(&infos, "laoma", 21);
  //push_front(&infos, "liuchen", 19);
  //push_front(&infos, "liuwei", 20);
  //writeFile("tmp.txt", &infos);
  readFile("tmp.txt", &infos);
  show(&infos);
  return 0;
}

