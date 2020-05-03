#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

/*
  跳石板问题.
  从N跳到M, 每次只能跳当前石板的约数(因子), 求跳跃的最小次数
  具有重复子问题, 以及最优子结构, 可以采用动态规划
  dp[N] = 0;
  ...
  dp[i + j] = min(dp[i + j], dp[i] + 1)
  从第i个石板, 跳j个距离
*/

int min_step(int N, int M) {
  vector<int> dp(M + 1, INT_MAX);
  dp[N] = 0;
  for (int i = N; i <= M; ++i) {
    if (dp[i] == INT_MAX) {
      continue;
    }
    for (int j = 2; j <= sqrt(i); ++j) {
      if (i + j > M) {
        break;
      }
      if (i % j == 0) {
        dp[i+j] = min(dp[i+j], dp[i]+1);
        if (i/j != j && i + i/j <= M) {
          dp[i+i/j] = min(dp[i+i/j], dp[i]+1);
        }
      }
    }
  }
  if (dp[M] == INT_MAX) {
    return -1;
  } else {
    return dp[M];
  }
}

int main() {
  int N, M;
  while(cin >> N >> M) {
    cout << min_step(N, M) << endl;
  }
  return 0;
}
