#include <iostream>
using namespace std;

// new, delete运算符重载:
// 1. new的底层是封装了malloc, 对于内存分配失败会抛出bad_alloc异常
// 2. delete的底层是封装了free, 默认operator delete函数是不抛出异常的
//
// new[]与delete[]运算符重载:
// 1. new[]的底层是封装了malloc, 对于内存分配失败会抛出bad_alloc异常
// 参数作为元素个数, 编译器会根据元素类型计算出需要分配的大小
// 2. delete的底层是封装了free, 默认operator delete函数是不抛出异常的
//
// new, delete与new[] delete[]的混合使用?
// 1. 对于内置类型, 是可以的. 比如说int
// 因为new与new[]都是按字节进行分配, 返回这段内存的首地址
// delete与delete[]都是按照内存的首地址进行释放
// 2. 对自定义类型, 是不可以的. 比如说对象
// 1)因为在调用new时, 编译器认为是对单个对象进行分配, 
// 直接按照对象大小分配, 返回这段空间的首地址
// 2)在调用new[]时, 编译器认为是对一组对象进行分配,
// 因此先开辟4个字节来存贮对象个数, 然后按顺序循环为每个对象进行内存分配
// 3)在调用delete时, 编译器认为是对单个对象进行释放,
// 因此直接对对象的首地址进行释放
// 4)在调用delete[]时, 编译器认为是对一组对象进行释放,
// 因此先向上偏移4个字节获取对象的个数, 然后释放4字节空间, 
// 最后按照顺序循环将每个对象释放

void* operator new(size_t size) {
  void* p = malloc(size);
  if (p == nullptr) {
    throw bad_alloc();
  }
  cout << "malloc:" << p << endl;
  return p;
}
void operator delete(void* p) noexcept {
  cout << "delete:" << p << endl;
  free(p);
}

void* operator new[](size_t size) {
  void* p = malloc(size);
  if (p == nullptr) {
    throw bad_alloc();
  }
  cout << "malloc[]:" << p << endl;
  return p;
}
void operator delete[](void* p) noexcept {
  cout << "delete[]:" << p << endl;
  free(p);
}

int main() {
  int* p = new int(10);
  //delete[] p;
  delete p;
  int* q = new int[10];
  //delete q;
  delete[] q;
  return 0;
}

// noexcept:
// noexcept是C++有关异常的关键字, 来说明该操作或函数是不会抛出异常的.
// 1. 说明该操作或函数是不会抛出异常的, 避免编译器对该操作或函数进行异常处理的准备,
// 有助于编译器的优化, 有助于提高性能
// 2. 如果该操作或函数被noexcept修饰, 并且内部发生了异常, 则系统会调用terminal()
// 来终止程序
//
// 为什么C++11将delete运算符重载设置为noexcept?
// 1. 被noexcept修饰的操作或函数, 有利于编译器的优化, 提高性能
// 2. 因为delete会调用对象的析构函数, 为了使对象资源能够正常释放, 
// 析构函数不应该抛出异常, 因此提高了程序的安全性, 如果发生异常直接终止
