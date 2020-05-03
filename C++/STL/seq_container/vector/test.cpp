#include "Vector.h"
#include "String.h"

// 1.在push_back中实现接收右值, 并且在整个转发过程中参数的属性不变
// template <class Tp>
// void push_back(Tp&& val) {
//   if (full()) {
//      expand();
//   }
//   _alloc.construct(_last, std::forward<Tp>(val));
//   ++_last;
// }
// 2.push_back通过模板函数来实现接收类型的推演, 推演规则是依赖C++11提供的引用重叠
// 比如说Tp为String&, 那么val为String& &&, 推演为String&
// 如果说Tp为String&&, 那么val为String&& &&, 推演为String&&
// 3.由于右值引用变量本身是一个左值, 因此要保证右值引用变量保持右值属性需要std::forward完美转发
// 保证在整个转发过程中类型的属性不变

int main() {
  Vector<String> v(10);
  String s1("sock");
  cout << "-----------------" << endl;
  v.push_back(std::move(s1));
  v.push_back(String("sock"));
  cout << "-----------------" << endl;
  return 0;
}
