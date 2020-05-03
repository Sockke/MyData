#include <iostream>
#include <stdio.h>

// 打印指定类型数据的值的16进制表示方式
void show_bytes(unsigned char* start, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%.2x ", start[i]);
  }
  std::cout << std::endl;
}
void show_int(int x) {
  show_bytes((unsigned char*)&x, sizeof(int));
}
void show_float(float x) {
  show_bytes((unsigned char*)&x, sizeof(float));
}
void show_pointer(void* x) {
  show_bytes((unsigned char*)&x, sizeof(void*));
}

int main() {
  show_int(100);
  show_float(100.0);
  int a = 1;
  int* p = &a;
  show_pointer(p);
  return 0;
}
