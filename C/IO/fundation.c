#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>

// 如何判断文件结尾
// feof+文件读函数返回值判断
// 1. feof通过判断文件结尾的标识符来检测是否到达文件结尾
// 2. feof是先读取后判断, 因此在循环读取文件过程中, 还要判断读文件函数的返回值,
// 如果返回值符合预期, 再进行数据的操作, 否则会操作到文件结尾后的数据
//
// feof与EOF的区别
// 1. feof是函数, 而EOF是一个宏(-1)
// 2. feof通过判断文件结尾的标识符, 并且是先读取后判断
// 而EOF是通过比对文本文件结尾的标识符, 也就是说EOF只能用于判断文本文件的结尾
//
// 文件操作流程:
// 1. 文件操作一般分为二进制操作和文本操作(ASCII)
//  文本文件与二进制文件的区别:
//  1. 编码方式不同, 文本文件是针对字符编码, 比如说ASCII, Unicode,
//  二进制文件是针对值编码, 比如int值, char值
//  2. 存贮方式不同, 虽然两者的存储格式都是二进制存贮, 但是在存储方式上有所差别,
//  因为文本文件是字符编码, 因此每个字符至少占1个字节,
//  二进制文件是值编码, 有的数据可能按位存储
//  3. 操作性能不同, 文本操作需要将内存中的数据进行编码, 然后写入磁盘,
//  二进制操作是将内存中的数据直接写入磁盘, 操作性能上要稍微高一些
//  (如果要求向终端或文本文件中显示内容, 使用文本操作方式, 否则尽量使用二进制操作方式)
//
// 2. 二进制操作一般是fwrite+fread
// 文本操作一般是fprintf+fscanf最常用, 因为需要显示, 则需要自定义格式
// 3. 文件操作的其他常用函数: fseek(文件流指针的跳转), rewind(文件流指针的重置)
// ferror(文件流指针的错误判断)

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
bool empty(AllInfo* infos) {
  assert(infos != NULL);
  return infos->_infos->_next == NULL;
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

#if 0
/*
  二进制读写文件
*/
void writeBinFile(const char* filename, AllInfo* infos) {
  assert(filename != NULL && infos != NULL);
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) {
    perror("file open error");
    exit(-1);
  }
  Info* cur = infos->_infos->_next; 
  while (cur != NULL) {
    fwrite((char*)cur, sizeof(*cur), 1, fp);
    cur = cur->_next;
  }
  fclose(fp);
}

void readBinFile(const char* filename, AllInfo* infos) {
  assert(filename != NULL && infos != NULL);
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    perror("file open error");
    exit(-1);
  }
  // feof判断是否读到文件结尾
  // feof是先读后判断, 因此循环读取文件时需要判断数据读取函数的返回值
  // 如果返回值符合预期再进行操作, 否则会操作到文件结尾后的数据
  while (!feof(fp)) {
    Info info;
    int ret = fread((char*)&info, sizeof(info), 1, fp);
    if (ret > 0) {
      push_front(infos, info._name, info._age);
    }
  }
  fclose(fp);
}
#endif

/*
  文本格式读写文件
*/
void writeTextFile(const char* filename, AllInfo* infos) {
  assert(filename != NULL && infos != NULL);
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    perror("file open error");
    exit(-1);
  }
  Info* cur = infos->_infos->_next;
  while (cur != NULL) {
    fprintf(fp, "%s %d\n", cur->_name, cur->_age);
    cur = cur->_next;
  }
  fclose(fp);
}

void readTextFile(const char* filename, AllInfo* infos) {
  assert(filename != NULL && infos != NULL);
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("file open error");
    exit(-1);
  }
  // feof是先读后判断, 因此循环读取文件时需要判断数据读取函数的返回值
  // 如果返回值符合预期再进行操作, 否则会操作到文件结尾后的数据
  while (!feof(fp)) {
    char name[30] = {0};
    int age = 0;
    int ret = fscanf(fp, "%s%d", name, &age);
    if (ret > 0) {
      push_front(infos, name, age);
    }
  }
}

void show(AllInfo* infos) {
  assert(infos != NULL);
  Info* cur =infos->_infos->_next;
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
  //writeTextFile("tmp.txt", &infos);
  readTextFile("tmp.txt", &infos);
  show(&infos);
  return 0;
}
