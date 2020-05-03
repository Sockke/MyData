#include <iostream>

// 类型强转判断大小端
int is_small() {
  int num = 1;
  char ch = (char)num;
  if (ch == 1) {
    return 1;
  } else {
    return 0;
  }
}
// 联合判断大小端
typedef union {
  int num;
  char ch;
}endian;
int is_small2() {
  endian e;
  e.num = 1;
  if (e.ch == 1) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  if (is_small()) {
    std::cout << "小端" << std::endl;
  } else {
    std::cout << "大端" << std::endl;
  }

  if (is_small2()) {
    std::cout << "小端" << std::endl;
  } else {
    std::cout << "大端" << std::endl;
  }
  return 0;
}

