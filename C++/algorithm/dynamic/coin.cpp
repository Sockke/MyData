#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 动态规划:
// 与分治类似, 原问题无法直接求解, 需要划分成子问题.
// 一般具有重复子问题以及最优子结构的问题适合用动态规划求解.
// 动态规划通过一个dp表来记录每个子结构的最优状态,
// 然后通过子结构的最优状态合并成原问题的最优解

/*
  硬币问题:
  有1, 3, 5分面额的硬币, 给定一个数字, 求能组成该数字所需要的最少的硬币数量
*/

#if 0
// 分治法进行求解
int divide(int num) {
  if (num == 1 || num == 3 || num == 5) {
    return 1;
  } 
  if (num == 2 || num == 4) {
    return 2;
  }
  int n1 = divide(num - 1) + 1; // 选择1分硬币
  int n2 = divide(num - 3) + 1; // 选择3分硬币
  int n3 = divide(num - 5) + 1; // 选择5分硬币
  return min({n1, n2, n3});
}

int main() {
  int num = 18;
  int min_num = divide(num);
  cout << min_num << endl;
  return 0;
}
#endif

/*
  dp[0] = 0
  dp[1] = 1 + dp[0] = 1
  dp[2] = 1 + dp[1] = 2
  dp[3] = 1 + min(dp[2], dp[0]) = 1 + dp[0] = 1;
  dp[4] = 1 + min(dp[3], dp[1]) = 1 + dp[3] = 2;
  dp[5] = 0
*/

int main() {
  int num = 18;
  vector<int> v{1, 3, 5};
  vector<int> dp(num + 1, 0);
  // 考虑边界并初始化
  for (int i = 1; i <= num; ++i) {
    dp[i] = i;
  }
  // 状态转移方程:
  // dp[i] = min(dp[i-v]) + 1
  // i: 总面额    v: 硬币面额
  for (int i = 1; i <= num; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i >= v[j]) {
        dp[i] = min(dp[i], dp[i - v[j]] + 1);
      }
    }
  }
  cout << dp[num] << endl;
  return 0;
}
