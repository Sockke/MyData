#include <iostream>

// 1. 默认值从右向左给, 且必须是连续
// 2. 立即数传参要比变量传参少一个mov指令, 效率稍微高一点
// 3. 调用出可以给默认参数, 声明时也可以给默认参数
// 4. 函数可以声明多次, 但是默认参数只能出现一次

int sum(int a, int b = 20);
int sum(int a = 10, int b);

int main() {
  int a = 10;
  int b = 20;
  int ret = sum(a, b);
  std::cout << "ret = " << ret << std::endl;
  return 0;
}

int sum(int a, int b) {
  return a + b;
}
