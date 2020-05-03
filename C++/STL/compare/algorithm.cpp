#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

int main() {
  std::vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(rand() % 100 + 1);
  }
  std::sort(v.begin(), v.end(), std::greater<int>());
  std::for_each(v.begin(), v.end(), [](int val)->void{
    std::cout << val << " ";
  });
  std::cout << std::endl;

  std::reverse(v.begin(), v.end());

  bool ret = std::binary_search(v.begin(), v.end(), 36);
  if (ret) {
    std::cout << "36 is found" << std::endl;
  }

  // 找到第一个比60大的值的迭代器
  //auto vit = std::find_if(v.begin(), v.end(), [](int val)->bool{
  //  return val > 60;
  //});
  // 也可以通过绑定器, 来绑定二元函数对象的一个参数, 使之变成一元函数对象
  auto vit = std::find_if(v.begin(), v.end(), std::bind1st(std::less<int>(), 60));
  v.insert(vit, 60);

  std::for_each(v.begin(), v.end(), [](int val)->void{
    std::cout << val << " ";
  });
  std::cout << std::endl;
  return 0;
}
