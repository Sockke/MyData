#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
  top k问题:
  1. 使用大根堆/小根堆来解决
  2. 使用快排的划分来解决
*/

int main() {
  vector<int> nums;
  for (int i = 0; i < 10000; ++i) {
    nums.push_back(rand());
  }
#if 0
  // 求前10大的, 定义一个小根堆
  priority_queue<int, vector<int>, greater<int>> q;
  // 将前10个数来构建小根堆
  for (int i = 0; i < 10; ++i) {
    q.push(nums[i]);
  }
  // 剩下的数与小根堆的堆顶进行比较
  // 如果比最小值还小, 说明肯定不是前10大的
  // 如果比最小值大, 那么可能是前10大的, 把堆顶的最小值pop掉, 将当前值push进去
  for (int i = 10; i < 10000; ++i) {
    int data = q.top();
    if (nums[i] > data) {
      q.pop();
      q.push(nums[i]);
    }
  }
  // 打印前10大的数
  while (!q.empty()) {
    int data = q.top();
    cout << data << " ";
    q.pop();
  }
  cout << endl;
#endif
  return 0;
}
