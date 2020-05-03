#include <iostream>
using namespace std;

// 1. const 修饰的是里自己最近的类型, 去掉修饰的类型就是不能更改的量
// 2. const右边没有*的话, 则不参与类型(比如说int* const 与 int* 的类型是相同的)
// 3. const与多级指针相结合的时候, 要考虑多级指针解引用与其他指针指向同一块地址的情况
//
// const 与一级指针结合的方式:
// 1. const int* p
// 2. int* const p
//
// const 与一级指针转换的公式:
// int* = const int*    // 错误
// const int* = int*    // 正确
#if 0
int main() {
  // 可以
  int a = 10; 
  const int* p1 = &a; // const int* <= int*
  int* const p2 = &a; // int* <= int*
  // 不行
  const int b = 10;
  int* q1 = &b; // int* <= const int*
  int* const q2 = &b; // int* <= const int*
  return 0;
}
#endif

// const 与二级指针结合的方式
// 1. const int** p
// 2. int* const* p
// 3. int** const p
//
// const 与二级指针转换的公式:
// int** = const int**      错误
// const int** = int**      错误
// int** = int* const*      错误 
// int* const* = int**      正确
#if 0
int main() {
  // 不行
  // 原因: **q不能改变, 如果&p赋给他, 那么*p可以间接改变**q
  int a = 10;
  //int* p = &a; 
  //const int** q = &p; // const int** <= int**
  
  // 修正: 防止产生歧义, 要么使*q与p具有相同的性质, 要么就不让*q指向p
  // 使*q与p具有相同的性质
  const int* p1 = &a; 
  const int** q1 = &p1;
  // 不让*q指向p
  int* p2 = &a;
  int* const* q2 = &p2; // 或者const int* const* q2 = &p2
  return 0;
}
#endif

// 例题:
int main() {
  // 错误的
  //int a = 10;
  //int* const p = &a;  
  //int** q = &p; int** <= int* const* --> int* <= const int*

  // 错误的
  //int a = 10;
  //const int* p = &a;
  //int* const* q = &p; int* const*<=const int**  --> int* <= const int*
  return 0;
}
