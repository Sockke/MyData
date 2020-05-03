#include <iostream>
#include <algorithm>
#include <vector>
#include "bind12.h"
using std::cout;
using std::endl;

// C++ STL中的绑定器: 就是将库中的二元函数对象转化为一元的函数对象
// 1. std::bind1st, 将operator()的第一个参数绑定为一个确定的值
// 2. std::bind2nd, 将operator()的第二个参数绑定为一个确定的值
//
// bind1st与bind2nd的实现原理
// 1. 他们都是一个模板函数, 接收一个二元函数对象和一个元素值, 返回一个一元函数对象
// 2. 一元函数对象提供operator(), 里面封装了二元函数对象, 
// 因此一元函数对象本质是对库中二元函数对象的封装

template <class Container>
void showContainer(Container& con) {
  typename Container::iterator it = con.begin();
  while (it != con.end()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
}

int main() {
  std::vector<int> v; 
  srand(time(nullptr));
  for (int i = 0; i < 10; ++i) {
    v.push_back(rand() % 100 + 1);
  }
  showContainer(v);
  std::sort(v.begin(), v.end(), std::greater<int>());
  showContainer(v);
  //auto it = std::find_if(v.begin(), v.end(), std::bind1st(std::greater<int>(), 70));
  //auto it = std::find_if(v.begin(), v.end(), std::bind2nd(std::less<int>(), 70));
  //auto it = std::find_if(v.begin(), v.end(), myBind1st(std::greater<int>(), 70));
  auto it = myFind_if(v.begin(), v.end(), myBind2nd(std::less<int>(), 70));
  if (it != v.end())  {
    v.insert(it, 70);
  }
  showContainer(v);
  return 0;
}
