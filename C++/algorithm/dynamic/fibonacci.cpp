#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dynamic(int n) {
  // 考虑边界
  if (n == 1 || n == 2) {
    return 1;
  }
  vector<int> dp(n, 0);
  // 初始化
  dp[0] = 1; // 第一个
  dp[1] = 1; // 第二个
  // 状态转移方程:
  // dp[i] = dp[i-1] + dp[i-2]
  for (int i = 2; i < n; ++i) { // 从第3个数开始
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n - 1];
}

int main() {
  int n = 10;
  int result = dynamic(n);
  cout << result << endl;
  return 0;
}
