#include <iostream>
using namespace std;

// const_cast去掉指针或引用常量属性的类型转换
// 1. 只能强转具有常性的指针或引用类型
// 2. 只能强转成去掉常属性后的指针或引用类型

int main() {
  volatile const int a = 10;
  int* p = const_cast<int*>(&a);
  *p = 10;
  cout << "a = " << a << endl;

  volatile const int* b = &a;
  int* q = const_cast<int*>(b);
  *q = 30;
  cout << "a = " << a << endl;
  return 0;
}

