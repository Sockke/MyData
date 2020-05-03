//#include "String.h"
#include "last_string.h"
#include "last_vector.h"
using namespace std;

// 迭代器: 想指针一样来遍历容器的元素
// 为什么使用迭代器:
// 1. 迭代器统一了遍历容器元素的操作, 对于不同容器, 你不需要知道它的底层是数组, 红黑树还是哈希桶,
// 我只需要像指针使用它即可, 因此泛型算法接收的参数都是迭代器
// 2. 迭代器重载了operator!=, operator*, operator++, operator->等运算符
// 在容器中提供begin()与end()方法来确定有效元素的起始和结束位置
// 3. for_each的底层起始是使用了迭代器来遍历, 只有容器支持迭代器才能使用for_each

int main() {
  Vector<String> v;
  v.push_back("sock");
  v.push_back("is");
  v.push_back("a");
  v.push_back("good");
  v.push_back("man");
  v.push_back("!");
  //Vector<String>::Iterator vit = v.begin();
  //while (vit != v.end()) {
  //  cout << *vit << " ";
  //  ++vit;
  //}
  for (const auto& e : v) {
    cout << e << " ";
  }
  cout << endl;
  //Vector<int> v;
  //v.push_back(1);
  //v.push_back(2);
  //v.push_back(3);
  //v.push_back(4);
  //v.push_back(5);
  //v.push_back(6);
  //while (!v.empty())  {
  //  cout << v.back() << " ";
  //  v.pop_back();
  //}
  //cout << endl;
  return 0;
}

#if 0
int main() {
  String s = "sock";
  String::Iterator sit = s.begin();
  while (sit != s.end()) {
    cout << *sit << " ";
    sit++;
  }
  cout << endl;
  //for (const auto& e : s) {
  //  cout << e << " ";
  //}
  //cout << endl;
  //String s = "sock";
  //auto it = s.begin();
  //while (it != s.end()) {
  //  if (*it == 'o') {
  //    *it = '_';
  //  }
  //  ++it;
  //}
  //cout << s << endl;
  return 0;
}
#endif

#if 0
int main() {
  String s1 = "hello";
  String s2 = "world";
  String s = s1 + s2;
  cout << "s1 + s2:" << s << endl;
  if (s1 > s2) {
    cout << s1 << ">" << s2 << endl;
  } else {
    cout << s1 << "<=" << s2 << endl;
  }
  return 0;
}
#endif
