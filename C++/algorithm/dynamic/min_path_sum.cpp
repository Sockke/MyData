#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
  三角矩阵, 自上而下, 求最短路径和
     [2]
    [3,4]
   [6,5,7]
  [4,1,8,3]
  最短路径和 = 2 + 3 + 5 + 1 = 11

  2
  3 4
  6 5 7
  4 1 8 3
  if j==0:
    dp[i][j] = dp[i-1][j]+arr[i][j]
  elif j==i:
    dp[i][j] = dp[i-1][j-1]+arr[i][j]
  else:
    dp[i][j] = max(dp[i-1][j-1], dp[i-1][j])+arr[i][j]
*/

#if 0
int shortest_path(vector<vector<int>>& triangle) {
  // 考虑边界
  if (triangle.empty()) {
    return 0;
  }
  int size = triangle.size();
  vector<vector<int>> dp(triangle);
  // 初始化
  dp[0][0] = triangle[0][0];
  // 状态转移方程
  for (int i = 1; i < size; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (j == 0) { // 最左侧
        dp[i][j] = dp[i - 1][j] + triangle[i][j];
      } else if (j == i) { // 最右侧
        dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
      } else {
        dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
      }
    }
  }
  int minsum = INT_MAX;
  for (auto& e : dp[size - 1]) {
    minsum = min(minsum, e);
  }
  return minsum;
}
#endif

/*
  空间复杂度为O(N)
*/
int shortest_path(vector<vector<int>>& triangle) {
  // 考虑边界
  if (triangle.empty()) {
    return 0;
  }
  int size = triangle.size();
  vector<int> dp(size, 0);
  // 初始化
  dp[0] = triangle[0][0];
  // 状态转移方程
  for (int i = 1; i < size; ++i) {
    for (int j = i; j >= 0; --j) {
      if (j == 0) { // 最左侧
        dp[j] = dp[j] + triangle[i][j];
      } else if (j == i) { // 最右侧
        dp[j] = dp[j - 1] + triangle[i][j];
      } else {
        dp[j] = min(dp[j - 1], dp[j]) + triangle[i][j];
      }
    }
  }
  int minsum = INT_MAX;
  for (auto& e : dp) {
    cout << e << " ";
    minsum = min(minsum, e);
  }
  cout << endl;
  return minsum;
}

int main() {
  vector<vector<int>> triangle;
  triangle.push_back({2});
  triangle.push_back({3, 4});
  triangle.push_back({6, 5, 7});
  triangle.push_back({4, 1, 8, 3});
  int minsum = shortest_path(triangle);
  cout << minsum << endl; // 11
  return 0;
}
