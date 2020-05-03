#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(rand() % 100 + 1);
  }
  std::vector<int>::reverse_iterator rvit = v.rbegin();
  while (rvit != v.rend()) {
    if (*rvit % 2 == 0) {
      *rvit = 0;
    }
    ++rvit;
  }
  std::vector<int>::const_reverse_iterator crvit = v.rbegin();
  while (crvit != v.rend()) {
    std::cout << *crvit <<  " ";
    ++crvit;
  }
  std::cout << std::endl;
#if 0
  std::vector<int>::iterator vit = v.begin();
  while (vit != v.end()) {
    if (*vit % 2 == 0) {
      vit = v.erase(vit);
    } else {
      ++vit;
    }
  }
  std::vector<int>::const_iterator cvit = v.begin();
  while (cvit != v.end()) {
    std::cout << *cvit << " ";
    ++cvit;
  }
  std::cout << std::endl;
#endif
  return 0;
}
