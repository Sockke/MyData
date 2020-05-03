#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
  统计重复数据, 去重
  1. 哈希表来统计
*/

int main() {
  vector<int> nums;
  for (int i = 0; i < 10000; ++i) {
    nums.push_back(rand() % 1000);
  }
  // 定义hash表
  unordered_map<int, int> m;
  // 统计每个数字出现的次数
  for (auto& e : nums) {
    ++m[e];
  }
  // 打印重复的数字及出现的次数
  for (auto& e : m) {
    if (e.second > 1) {
      cout << e.first << ":" << e.second << endl;
    }
  }
  return 0;
}
