#include <iostream>
#include <vector>
#include "last_vector.h"
using namespace std;

// 迭代器失效:
// 1. 当容器调用erase方法后, 当前位置到容器的末尾元素的所有迭代器全部失效
// 2. 当容器调用insert方法后, 当前位置到容器的末尾元素的所有迭代器全部失效
// 3. 当容器调用insert并引起扩容后, 该容器所有元素的迭代器全部失效
//
// 迭代器失效是否引发错误在vs与linux上是不同的, 但是当容器需要调用erase和insert方法
// 来操作迭代器时, 一定要返回将迭代器更新
//
// 迭代器失效的原理: vs
// 将指向容器中每个元素位置的迭代器交给一个链表来管理,
// 当对元素进行增删的操作时, 根据迭代器失效的原则, 将链表中管理的该迭代器对象的结点释放,
// 并将失效的迭代器对象中迭代的容器指针置空, 表示指向该容器元素的迭代器失效
// 当对迭代器失效后, 再次对失效的迭代器进行运算符的操作, 则会抛出异常
//
// 在linux下有所区别

int main() {
  Vector<int> v;
  v.push_back(9);
  v.push_back(5);
  v.push_back(2);
  v.push_back(7);
  auto it = v.begin();
  while (it != v.end()) {
    if (*it % 2 == 0) {
      it = v.Insert(it, *it - 1);
      ++it;
    } 
  }
  for (auto& e : v) {
    cout << e << " ";
  }
  cout << endl;
  //auto it1 = v.end();
  //v.pop_back();
  //auto it2 = v.end();
  //cout << (it1 != it2) << endl;
  //cout << "-----------" << endl;
  //for (auto& e : v) {
  //  cout << e << " ";
  //}
  //cout << endl;
  //auto vit = v.end();
  //v.pop_back();
  //auto vit2 = v.end();
  //cout << (vit != vit2) << endl;
  //while (vit != v.end()) {
  //  if (*vit % 2 == 0) {
  //  
  //  }
  //}
  return 0;
}

#if 0
int main() {
  vector<int> v{9, 5, 2, 7};
  v.reserve(6);

  auto vit = v.begin();
  while (vit != v.end()) {
    if (*vit % 2 != 0) {
      v.erase(vit); // 迭代器失效
    } else {
      ++vit;
    }
  }
  
  //cout << "capacity:" << v.capacity() << endl;
  //auto vit = v.begin();
  //while (vit != v.end()) {
  //  //if (*vit % 2 == 0) {
  //  //  v.erase(vit);
  //  //}
  //  if (*vit % 2 == 0) {
  //    v.insert(vit, *vit - 1); // 迭代器失效
  //    ++vit;
  //  }
  //  ++vit;
  //}
  for (auto& e : v) {
    cout << e << " ";
  }
  cout << endl;
  //auto it = v.end();
  //v.pop_back();
  //auto it2 = v.end();
  //cout << (it == it2) << endl; // it迭代器失效, 不能进行比较
  return 0;
}
#endif
