#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
  01背包问题, 使用动态规划进行求解
  背包容量: N
  物品体积: W
  物品价值: V

  dp[i][j]: 背包容量为j时, 前i+1个物品最多能装的最大价值

  if i < W[j]: // 装不下
    dp[i][j] = dp[i-1][j]
  else:        // 能装下, 可以选择装, 也可选择不装
    dp[i][j] = max(dp[i-1][j], dp[i-1][j-W[i-1]]+V[i-1])
*/

vector<vector<int>> dp2;
int dynamic(vector<int>& W, vector<int>& V, int N) {
  if (W.empty() || N == 0) {
    return 0;
  }
  int len = W.size();
  vector<vector<int>> dp(len+1, vector<int>(N+1, 0));
  for (int i = 1; i <= len; ++i) {
    for (int j = 1; j <= N; ++j) {
      // 不能装下该物品
      if (W[i-1] > j) {
        dp[i][j] = dp[i-1][j];
      } else {
        // 能装下该物品
        dp[i][j] = max(dp[i-1][j], dp[i-1][j-W[i-1]] + V[i-1]);
      }
    }
  }
  return dp[len][N];
}
int dynamic2(vector<int>& W, vector<int>& V, int N) {
  if (W.empty() || N == 0) {
    return 0;
  }
  int len = W.size();
  vector<int> dp(N+1, 0);
  for (int i = 1; i <= len; ++i) {
    for (int j = N; j > 0; --j) {
      if (W[i-1] > j) {
        dp[j] = dp[j];
      } else {
        dp[j] = max(dp[j], dp[j-W[i-1]]+V[i-1]);
      }
    }
  }
  return dp[N];
}

#if 0
void showPath(vector<int>& W, vector<int>& V, int i, int j) {
  if (i == 0) {
    return;
  }
  if (dp2[i][j] != dp2[i][j-1]) { // 选了
    showPath(W, V, i-W[j-1], j-1);
    cout << W[j-1] << " ";
  } else { // 没选
    showPath(W, V, i, j-1);
  }
}
#endif

int main() {
  int N = 20;
  vector<int> W{12, 5, 8, 9, 6};
  vector<int> V{9, 11, 4, 7, 8};
  int maxValue = dynamic2(W, V, N);
  //showPath(W, V, N, W.size());
  //cout << endl;
  cout << maxValue << endl;
  return 0;
}
