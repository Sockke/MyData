#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

#if 0
/*
  查找两个字符串a,b中的最长公共子串。若有多个，输出在较短串中最先出现的那个。
*/

string MCS(string& s1, string& s2) {
  int len1 = s1.size();
  int len2 = s2.size();
  int start = 0, maxlen = 0;
  // 存放公共子串长度
  vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0));
  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (s1[i-1] == s2[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      }
      if (dp[i][j] > maxlen) {
        maxlen = dp[i][j];
        start = i - maxlen;
      }
    }
  }
  return s1.substr(start, maxlen);
}

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    // 因为要求短串中最先出现的
    if (s1.size() > s2.size()) {
      swap(s1, s2);
    }
    cout << MCS(s1, s2) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  计算两个字符串的最大公共字串的长度
*/

int maxLen(string& s1, string& s2) {
  if (s1.empty() || s2.empty()) {
    return 0;
  }
  int len1 = s1.size();
  int len2 = s2.size();
  vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
  int maxlen = 0;
  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (s1[i-1]==s2[j-1]) {
        dp[i][j] = dp[i-1][j-1]+1;
      }
      if (dp[i][j] > maxlen) {
        maxlen = dp[i][j];
      }
    }
  }
  return maxlen;
}

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    cout << maxLen(s1, s2) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  word1变成word2所需要的最少的操作次数
  可以删除, 可以添加, 也可以替换字符
*/

/*
int backtrace(string& s1, int i, string& s2, int j) {
  if (i == 0 && j == 0) {
    return 0;
  }
  if (i == 0 || j == 0) {
    return abs(j-i);
  }
  if (s1[i] == s2[j]) {
    return backtrace(s1, i - 1, s2, j - 1);
  } else {
    int cnt1 = 1 + backtrace(s1, i - 1, s2, j); //删
    int cnt2 = 1 + backtrace(s1, i, s2, j - 1); // 添加
    int cnt3 = 1 + backtrace(s1, i - 1, s2, j - 1); // 替换
    return min(min(cnt1, cnt2), cnt3);
  }
}
*/
// 1. 字符相同, min(删除, 添加, 不动)
// 2. 字符不相同, min(删除, 添加, 替换)
int minDistance(string& s1, string& s2) {
  if (s1.empty()) {
    return s2.size();
  }
  if (s2.empty()) {
    return s1.size();
  }
  int len1 = s1.size();
  int len2 = s2.size();
  vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
  // 考虑边界并初始化
  for (int i = 1; i <= len1; ++i) {
    dp[i][0] = i;
  }
  for (int i = 1; i <= len2; ++i) {
    dp[0][i] = i;
  }
  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      // 删除word1一个字符, 或者为word1添加1个字符
      dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1);
      if (s1[i-1] == s2[j-1]) {
        // 如果当前字符相同, 不需要调整, 与调整的取最小值
        dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
      } else {
        // 当前字符不相同, 还可以考虑替换, 三者取最小值
        dp[i][j] = min(dp[i][j], dp[i-1][j-1] + 1);
      }
    }
  }
  return dp[len1][len2];
}

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    cout << minDistance(s1, s2) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  6*6矩阵网格, 网格中带有权值,
  从左上角走到右下角所经过的权值之和最大为多少,
  只能向右走, 或向下走
*/

class Bonus {
  public:
    int getMost(vector<vector<int> > board) {
      int size = board.size();
      vector<vector<int>> dp(size + 1, vector<int>(size + 1, 0));
      for (int i = 1; i <= size; ++i) {
        for (int j = 1; j <= size; ++j) {
          // dp[i-1][j]往下走过来的, dp[i][j-1]往右走过来的
          dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + board[i-1][j-1];
        }
      }
      return dp[size][size];
    }
};
#endif

#if 0
class Solution {
  public:
    /*
    // 找规律
    int jumpFloorII(int number) {
      if (number <= 0) {
        return 0;
      }
      int jumpCounts = 1;
      jumpCounts = jumpCounts << (number - 1);
      return jumpCounts;
    }
    */
    /*
    // 采用回溯解决
    // f(1) = 1
    // f(2) = f(1) + 1
    // f(3) = f(1) + f(2) + 1
    // f(n-1) = f(1) + f(2) + ... + f(n-2) + 1
    // f(n) = f(1) + f(2) + ... + f(n-2) + f(n-1) + 1
    // => f(n) = 2*f(n-1)
    int jumpFloorII(int number) {
      if (number <= 0) {
        return 0;
      }
      if (number == 1) {
        return 1;
      } else {
        return 2 * jumpFloorII(number - 1);
      }
    }
    */
    // 动态规划解决
    int jumpFloorII(int number) {
      if (number <= 0) {
        return 0;

      }
      vector<int> dp(number + 1, 1);
      dp[1] = 1;
      for (int i = 2; i <= number; ++i) {
        for (int j = i - 1; j >= 1; --j) {
          dp[i] += dp[j];
        }
      }
      return dp[number];
    }
};
#endif

#if 0
/*
  小易来到了一条石板路前，每块石板上从1挨着编号为：1、2、3.......
  这条石板路要根据特殊的规则才能前进：对于小易当前所在的编号为K的石板，
  小易单次只能往前跳K的一个约数(不含1和K)步，即跳到K+X(X为K的一个非1和本身的约数)的位置。 
  小易当前处在编号为N的石板，他想跳到编号恰好为M的石板去，小易想知道最少需要跳跃几次可以到达。
  例如：
  N = 4，M = 24：
  4->6->8->12->18->24
  于是小易最少需要跳跃5次，就可以从4号石板跳到24号石板

   dp[4] = 0;
   dp[6] = 1 + dp[4] = 1;
   dp[8] = 1 + dp[6] = 2;
   dp[9] = 1 + dp[6] = 2;
   dp[10] = 1 + dp[8] = 3;
   dp[12] = 1 + dp[8] = 3;
   dp[12] = min(dp[12], dp[9] + 1) = 3;
   dp[12] = min(dp[12], dp[10] + 1) = 3;
   dp[15] = dp[10] + 1 = 4;
   dp[14] = dp[12] + 1 = 4;
   dp[16] = dp[12] + 1 = 4;
   dp[18] = dp[12] + 1 = 4;
   dp[18] = min(dp[18], dp[15] + 1) = 4
   ...
*/
int min_step(int N, int M) {
  vector<int> dp(M + 1, INT_MAX);
  dp[N] = 0;
  for (int i = N; i <= M; ++i) {
    // 跳不到这里
    if (dp[i] == INT_MAX) {
      continue;
    }
    for (int j = 2; j <= sqrt(i); ++j) {
      if (i % j == 0) {
        if (i + j <= M) {
          dp[i + j] = min(dp[i + j], dp[i] + 1);
        }
        if (i + i/j <= M) {
          dp[i + i/j] = min(dp[i + i/j], dp[i] + 1);
        }
      }
    }
  }
  if (dp[M] == INT_MAX) {
    return -1;
  }
  return dp[M];
}

int main() {
  int N, M;
  cin >> N >> M;
  cout << min_step(N, M) << endl;
  return 0;
}                               
#endif
