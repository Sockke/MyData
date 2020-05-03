#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
// 模拟实现 atoi
int my_atoi(const char* str) {
  const char* left = str;
  while (*left != '\0') { // 确定第一个不为0的数字字符 --- left
    if (*left > '0' && *left <= '9') {
      break;
    } else if (isspace(*left) || *left == '0') {
      ++left;
    } else {
      return 0;
    }
  }
  const char* right = left;
  while (*right!= '\0') { // 确定最后一个数字字符的位置 --- right - 1
    if (*right >= '0' && *right <= '9') {
      ++right;
    } else {
      break;
    }
  }
  int sum = 0;
  while (left < right) { // 转换
    sum += (*left - '0') * pow(10, right - left - 1);
    ++left;
  }
  return sum;
}
int main() {
  //char ch = -128;
  //unsigned char* p = (unsigned char*)&ch;
  //printf("%.2x\n", p[0]);
  const char* s = "400";
  printf("%d\n", atoi(s));
  printf("%d\n", my_atoi(s));
  return 0;
}
