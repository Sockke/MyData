#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

static int cnt = 0;

#if 0
int divide(string& s1, int i, string& s2, int j) {
  // 考虑边界
  if (s1.empty() || s2.empty()) {
    return 0;
  }
  if (i < 0 || j < 0) {
    return 0;
  }
  ++cnt;
  if (s1[i] == s2[j]) {
    return 1 + divide(s1, i - 1, s2, j - 1);
  } else {
    int len1 = divide(s1, i - 1, s2, j);
    int len2 = divide(s1, i, s2, j - 1);
    return max(len1, len2);
  }
}
#endif

#if 0
vector<vector<int>> dp;
vector<vector<int>> path;
int divide(string& s1, int i, string& s2, int j) {
  // 考虑边界
  if (s1.empty() || s2.empty()) {
    return 0;
  }
  if (i < 0 || j < 0) {
    return 0;
  }
  if (dp[i][j] >= 0) {
    return dp[i][j];
  }
  ++cnt;
  if (s1[i] == s2[j]) {
    dp[i][j] = 1 + divide(s1, i - 1, s2, j - 1);
    path[i][j] = 1; // 沿对角线走
    return dp[i][j];
  } else {
    int len1 = divide(s1, i - 1, s2, j);
    int len2 = divide(s1, i, s2, j - 1);
    if (len1 >= len2) {
      dp[i][j] = len1;
      path[i][j] = 2; // 朝上走
    } else {
      dp[i][j] = len2; 
      path[i][j] = 3; // 朝左走
    }
    return dp[i][j];
  }
}

void showPath(string& s1, int i, int j) {
  if (i < 0 || j < 0) {
    return;
  }
  if (path[i][j] == 1) {
    showPath(s1, i - 1, j - 1);
    cout << s1[i] << " ";
  } else if (path[i][j] == 2) {
    showPath(s1, i - 1, j);
  } else {
    showPath(s1, i, j - 1);
  }
}

int main() {
  string s1 = "helloworld";
  string s2 = "chmelaord";
  int len1 = s1.size();
  int len2 = s2.size();
  dp.resize(len1);
  path.resize(len1);
  for (int i = 0; i < len1; ++i) {
    dp[i].resize(len2);
    path[i].resize(len2);
    for (int j = 0; j < len2; ++j) {
      dp[i][j] = -1;
    }
  }
  int result = divide(s1, len1 - 1, s2, len2 - 1);
  cout << result << endl; // helord  6
  cout << cnt << endl;
  for (int i = 0; i < len1; ++i) {
    for (int j = 0; j < len2; ++j) {
      cout << path[i][j] << " ";
    }
    cout << endl;
  }
  showPath(s1, len1 - 1, len2 - 1);
  return 0;
}
#endif

/*
  最长公共子序列, 用动态规划实现
  if s1[i] == s2[j]:
    dp[i][j] = 1 + dp[i-1][j-1]
  else:
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
*/

int LCS(string& s1, string& s2) {
  // 考虑边界
  if (s1.empty() || s2.empty()) {
    return 0;
  }
  int len1 = s1.size();
  int len2 = s2.size();
  vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
  for (int i = 1; i <= len1; ++i)  {
    for (int j = 1; j <= len2; ++j) {
      if (s1[i-1] == s2[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  return dp[len1][len2];
}

int main() {
  string s1 = "helloworld";
  string s2 = "chmelaord";
  int result = LCS(s1, s2);
  cout << result << endl;
  return 0;
}
