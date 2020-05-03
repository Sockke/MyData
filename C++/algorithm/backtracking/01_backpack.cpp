#include <iostream>
#include <vector>
using namespace std;

/*
  通过子集树来解决01背包问题
  有n个物品, 每个物品对应有价值,
  挑选一些物品放到容量为m的背包里, 使得总价值最大
*/

int weight[] = {12, 5, 8, 9, 6}; // 物品重量
int values[] = {9, 11, 4, 7, 8}; // 物品价值
int cap = 20; // 背包容量

const int len = sizeof(weight) / sizeof(weight[0]);
vector<int> aid; // 辅助数组, 已经挑选的物品
int has_select_w = 0;
int has_select_v = 0;
int max_value = 0;

vector<int> result;

void backpack(int i) {
  if (i == len) {
    if (has_select_v > max_value) {
      max_value = has_select_v;
      result = aid;
    }
    return;
  }
  // 如果已经选择重量+要选择的重量大于背包容量了, 就不要选择了
  if (has_select_w + weight[i] <= cap) {
    has_select_w += weight[i];
    has_select_v += values[i];
    aid.push_back(weight[i]);
    backpack(i + 1);
    has_select_w -= weight[i];
    has_select_v -= values[i];
    aid.pop_back();
  }
  // 如果已选择物品的价值+剩余未操作物品的总价值还小于最大价值, 就不要选择了
  int sum = 0;
  for (int k = i + 1; k < len; ++k) {
    sum += values[k];
  }
  if (has_select_v + sum > max_value) {
    backpack(i + 1);
  }
}

int main() {
  backpack(0);
  for (auto& e : result) {
    cout << e << " ";
  }
  cout << endl;
  cout << "max value:" << max_value << endl;
  return 0;
}
