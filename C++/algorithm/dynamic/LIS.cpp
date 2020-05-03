#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
  LIS: 最长上升子序列的长度, 不一定连续
  dp[0] = 1
  dp[1] = 1
  dp[2] = dp[1] + 1 = 2
  dp[3] = 1
  dp[4] = max(dp[0]+1,dp[1]+1,dp[2]+1,dp[3]+1) = dp[2]+1 = 3
  dp[5] = max(dp[0]+1,dp[1]+1,dp[2]+1,dp[3]+1) = dp[2]+1 = 3
  dp[6] = max(dp[0]+1...) = dp[5]+1 = 4
  dp[7] = max(dp[0]+1...) = dp[6]+1 = 5
*/

int LIS(vector<int>& arr) {
  // 考虑边界
  if (arr.empty()) {
    return 0;
  }
  int size = arr.size();
  // 初始化
  vector<int> dp(size, 1);
  // 状态转移方程
  for (int i = 1; i < size; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr[i] > arr[j]) { // 上升
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }
  int maxnum = INT_MIN;
  for (auto& e : dp) {
    maxnum = max(maxnum, e);
  }
  return maxnum;
}

int main() {
  vector<int> arr{5, 3, 4, 1, 8, 6, 7, 10};
  int result = LIS(arr);
  cout << result << endl;
  return 0;
}
