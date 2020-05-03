#include "String.h"
#include <vector>

// 在有些情况下, 必须要拷贝构造临时对象, 或者用临时对象进行赋值
// 此时就存在效率不高的问题.
// 1. 临时对象拷贝, 然后释放; 临时对象赋值开辟新内存拷贝, 然后释放.
// 2. 这些临时对象既然不要了, 完全可以将资源进行转移, 这样就避免了额外的拷贝
//
// 通过带右值引用的拷贝构造函数和赋值重载函数来解决
// 1. 右值引用参数, 接收临时对象(将亡值)
// 2. 在拷贝构造和赋值重载函数中, 不开辟堆内存, 
// 直接将临时对象的资源转移给当前对象, 而临时对象指向堆内存的指针置空即可

int main() {
  //String s1("hello ");
  //String s2("world");
  //String s3 = s1 + s2;
  //cout << s3 << endl;
  String s1("sock");
  std::vector<String> v;
  v.reserve(10);
  cout << "--------------------" << endl;
  v.push_back(s1);
  // 当元素对象实现了带右值参数的拷贝构造和赋值后
  // 这个过程先构造临时对象, 然后调用移动构造, 最后析构临时对象(不做任何事)
  v.push_back(String("sock"));
  cout << "--------------------" << endl;
  return 0;
}

#if 0
String getString(String& s) {
  String tmp(s.c_str());
  return tmp;
}

int main() {
  String s1("sock");
  String s2; 
  s2 = getString(s1);
  cout << s2.c_str() << endl;
  return 0;
}
#endif
