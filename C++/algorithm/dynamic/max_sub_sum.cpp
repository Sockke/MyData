#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
  分治是从后向前回溯
  动归是从前向后递推
*/
#if 0
int maxnum = INT_MIN;
int divide(vector<int>& arr, int i) {
  if (i == 0) {
    return arr[i] > 0 ? arr[i] : 0;
  }
  int curnum = divide(arr, i - 1) + arr[i];
  if (curnum < 0) {
    return 0;
  } else {
    maxnum = max(maxnum, curnum);
    return curnum;
  }
}

int main() {
  vector<int> arr{-2, 11, -4, 13, -5, -2};
  divide(arr, 5);
  cout << maxnum << endl;
  return 0;
}
#endif

#if 0
/*
  最大连续子段和:
  求连续的最大字段和, 当数组中元素全部为负数时, 返回0
  dp[0] = 0
  dp[1] = 11
  dp[2] = 7
  dp[3] = 20 
  dp[4] = 15
  dp[5] = 13
  ...
  if dp[i-1] + arr[j] < 0:
    dp[i] = 0
  else:
    dp[i] = dp[i-1] + arr[j]
*/

int dynamic(vector<int>& arr) {
  // 考虑边界
  if (arr.empty()) {
    return 0;
  }
  int size = arr.size();
  vector<int> dp(size + 1, 0);
  // 状态转移方程:
  // if dp[i-1] + arr[j] < 0:
  //  dp[i] = 0
  // else:
  //  dp[i] = dp[i-1] + arr[j]
  for (int i = 1; i <= size; ++i) {
    if (dp[i - 1] + arr[i - 1] < 0) {
      dp[i] = 0;
    } else {
      dp[i] = dp[i - 1] + arr[i - 1];
    }
  }
  int maxnum = 0;
  for (int i = 1; i <= size; ++i) {
    maxnum = max(maxnum, dp[i]);
  }
  return maxnum;
}

int main() {
  vector<int> arr{-2, 11, -4, 13, -5, -2};
  int result = dynamic(arr);
  cout << result << endl;
  return 0;
}
#endif

/*
  最大连续子段和:
  求连续的最大子段和, -1, -2, -5, -8最大连续子段和为-1
  -1, -2, 1, -8, -5最大连续子段和为1
  
  if dp[i-1] + arr[j] < 0:
    dp[i] = arr[j]
  else:
    dp[i] = max(dp[i - 1] + arr[j], arr[j]);
*/

int dynamic(vector<int>& arr) {
  // 考虑边界
  if (arr.empty()) {
    return 0;
  }
  int size = arr.size();
  vector<int> dp(arr);
  // 状态转移方程
  // dp=arr
  // dp[i] = dp[i-1] + arr[i]
  for (int i = 0; i < size; ++i) {
    dp[i] = max(dp[i], dp[i-1] + arr[i]);
  }
  int maxnum = dp[0];
  for (int i = 1; i < size; ++i) {
    maxnum = max(maxnum, dp[i]);
  }
  return maxnum;
}

int main() {
  //vector<int> arr{1,-2,3,10,-4,7,2,-5}; // 18
  vector<int> arr{-2,-8,-1,-5,-9};  // -1
  int maxnum = dynamic(arr);
  cout << maxnum << endl; 
  return 0;
}
