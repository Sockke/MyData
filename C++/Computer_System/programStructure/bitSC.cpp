#include <iostream>

// bit set --- 在m为1的每个位置, 将x设置为1
int bis(int x, int m) {
  return x | m;
}
// bit clear -- 在m为1的每个位置, 将x设置为0
int bic(int x, int m) {
  return x & (~m);
}
int main() {
  std::cout << bis(3, 5) << std::endl;
  std::cout << bic(3, 5) << std::endl;
  return 0;
}
