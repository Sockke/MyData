#include <stdio.h>
#include <sys/stat.h>

/*
  如何用C获取文件的大小?
  1. 通过fseek与ftell来获取文件的大小
    1)  先以二进制的格式将文件打开
    2)  然后通过fseek将文件流指针跳转到文件末尾
    3)  最后通过ftell来计算流指针的位置, 即距离起始位置的字节数
  2. 通过Linux中的stat信息中获取文件大小
    1) 定义struct stat文件结构体
    2) 通过stat来获取文件信息
    3) 最后通过statbuf.st_size来获取文件大小

  第一种存在一定的性能问题, 因为fseek跳转到文件结尾的前提是,
  需要将整个文件加载到内存中, 会影响性能
  Linux提供的系统调用stat仅仅将文件信息加载到内存中, 减少了性能的消耗
*/

long getFileSize(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fclose(fp);
  return size;
}

long getFileSize2(const char* filename) {
  struct stat statbuf;
  stat(filename, &statbuf);
  return statbuf.st_size;
}

int main() {
  const char* filename = "a.txt";
  printf("file size:%ld\n", getFileSize(filename));
  return 0;
}
