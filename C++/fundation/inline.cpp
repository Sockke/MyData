#include <iostream>
using namespace std;

// 1. inline函数与普通函数的区别
// inline函数是在编译阶段直接在调用处展开, 少了函数调用的开销(调用, 开辟, 回退)
// 2. inline函数由于在编译阶段直接在调用出展开, 则不生成相应的函数符号
// 3. inline函数是否展开是由编译器决定的, 一般是代码量少但是频繁调用的会展开
// inline只是对编译器的一个建议
// 4. 在debug版本下inline函数不会展开, 因为在debug版本下是需要支持调试的,
// 如果展开, 那么就无法进行调试; inline在release版本下才会根据情况展开
//

inline int sum(int a, int b) {
  return a + b;
}

int main() {
  int a = 10;
  int b = 20;
  int ret = sum(a, b); // 在调用处直接展开, 则变成int ret = a + b
  cout << "ret = " << ret << endl;
  return 0;
}
