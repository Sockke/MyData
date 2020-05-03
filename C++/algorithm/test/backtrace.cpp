#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#if 0
/*
  迷宫问题, 从左上角走到左下角, 输出最短路径信息
  1代表墙壁不能走, 0可以走, 只能上下左右走, 不能斜着走
  Sample Input
  0 1 0 0 0
  0 1 0 1 0
  0 0 0 0 0
  0 1 1 1 0
  0 0 0 1 0
  Sample Output
  (0, 0)
  (1, 0)
  (2, 0)
  (2, 1)
  (2, 2)
  (2, 3)
  (2, 4)
  (3, 4)
  (4, 4)
*/

vector<vector<int>> maze;
vector<pair<int, int>> aid;
vector<pair<int, int>> result;
int N, M;

void backtrace(int i, int j) {
  maze[i][j] = 1;
  aid.push_back({i, j});
  if (i == N - 1 && j == M - 1) {
    if (result.empty() || aid.size() < result.size()) {
      result = aid;
    }
  }
  if (i-1 >= 0 && maze[i-1][j] == 0) { 
    // 往上走
    backtrace(i - 1, j);
  } else if (j - 1 >= 0 && maze[i][j-1] == 0) {
    // 往左走
    backtrace(i, j - 1);
  } else if (j + 1 < M && maze[i][j + 1] == 0) {
    // 往右走
    backtrace(i, j + 1);
  } else if (i + 1 < N && maze[i + 1][j] == 0) {
    // 往下走
    backtrace(i + 1, j);
  }
  maze[i][j] = 0;
  aid.pop_back();
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    maze.clear();
    aid.clear();
    result.clear();
    N = n;
    M = m;
    maze.resize(n);
    for (int i = 0; i < n; ++i) {
      maze[i].resize(m);
      for (int j = 0; j < m; ++j) {
        cin >> maze[i][j];
      }
    }
    backtrace(0, 0);
    for (auto& e : result) {
      cout << "(" << e.first << "," << e.second << ")" << endl;
    }
  }
  return 0;
}
#endif

#if 0
/*
  给定三条边, 判断能不能组成一个三角形
  三角形: 任意两条边之和 > 第三边
  采用枚举的形式(子集树)来实现
*/
vector<double> arr(3, 0);
const int len = 3;
double has_select = 0;
double no_select = 0;
bool istriangle = true;
void such(int i, int cnt) {
  if (cnt == 0) {
    if (has_select <= no_select) {
      istriangle = false;
    }
  } else {
    for (int k = i; k < len; ++k) {
      has_select += arr[k];
      no_select -= arr[k];
      such(k + 1, cnt - 1);
      has_select -= arr[k];
      no_select += arr[k];
    }
  }
}

int main() {
  double a, b, c;
  while (cin >> a >> b >> c) {
    arr.clear();
    istriangle = true;
    has_select = 0;
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    no_select = a + b + c;
    such(0, 2);
    if (istriangle == true) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
  return 0;
}

// 直接简单求解
string isTriangle(double a, double b, double c) {
  bool ret = ((a+b)>c) && ((a+c)>b) && ((b+c)>a);
  return ret == true ? "Yes" : "No";
}

int main() {
  double a, b, c;
  while (cin >> a >> b >> c) {
    cout << isTriangle(a, b, c) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  最小不可组成和: 意思是子集和的最小值与最大值圈定的整数范围内,
  求最小的不能是子集和的数, 如果圈定的范围内都是子集的和, 那么返回最大子集和+1

  很明显的子集树问题
*/
class Solution {
  public:
    /*
     *  正数数组中的最小不可组成和
     *  输入：正数数组arr
     *  返回：正数数组中的最小不可组成和
     */
    void subset(vector<int>& arr, int len, int i, vector<int>& s) {
      if (i == len) {
        if (has_select > 0) {
          s.push_back(has_select);
        }
      } else {
        has_select += arr[i];
        subset(arr, len, i + 1, s);
        has_select -= arr[i];
        subset(arr, len, i + 1, s);
      }
    }
    int getFirstUnFormedNum(vector<int> arr, int len) {
      vector<int> s;
      subset(arr, len, 0, s);
      sort(s.begin(), s.end());
      int size = s.size();
      int i = 1;
      for (; i < size; ++i) {
        if (s[i] - s[i-1] > 1) {
          return s[i-1] + 1;
        }
      }
      return s[i-1] + 1; 
    }
    static int has_select;
};
int Solution::has_select = 0;
#endif

#if 0
/*
  问题描述：给出4个1-10的数字，通过加减乘除，得到数字为24就算胜利
  输入：
  4个1-10的数字。[数字允许重复，但每个数字仅允许使用一次，测试用例保证无异常数字]
  输出：
  true or false

  排列树 + 枚举
*/
vector<double> arr(4, 0);
const int size = 4;
bool ret = false;
bool such(int i, double num) {
  if (i == size) {
    return num == 24;
  }
  for (int k = i; k < size; ++k) {
    if(such(k + 1, num + arr[k])
        || such(k + 1, num - arr[k])
        || such(k + 1, num * arr[k])
        || such(k + 1, num / arr[k])) {
      return true;
    }
  }
  return false;
}
void arrange(int i) {
  if (i == size) {
    if (such(0, 0) == true) {
      ret = true;
    }
  } else {
    for (int k = 0; k < size; ++k) {
      swap(arr[k], arr[i]);
      arrange(i + 1);
      swap(arr[k], arr[i]);
    }
  }
}
int main() {
  while (cin >> arr[0] >> arr[1] >> arr[2] >> arr[3]) {
    ret = false;
    arrange(0);
    if (ret == true) {
      cout << "true" << endl;
    } else {
      cout << "false" << endl;
    }
  }
  return 0;
}
#endif

#if 0
/*
一个袋子里面有n个球，每个球上面都有一个号码(拥有相同号码的球是无区别的)。
如果一个袋子是幸运的当且仅当所有球的号码的和大于所有球的号码的积。
例如：如果袋子里面的球的号码是{1, 1, 2, 3}，这个袋子就是幸运的，
因为1 + 1 + 2 + 3 > 1 * 1 * 2 * 3
你可以适当从袋子里移除一些球(可以移除0个,但是别移除完)，要使移除后的袋子是幸运的。
现在让你编程计算一下你可以获得的多少种不同的幸运的袋子。
*/

vector<int> arr{1, 1, 2, 2};
int size = arr.size();

int sum = 0;
int multi = 1;
int cnt = 0;

// 采用枚举法
void such(int i) {
  if (i == size) {
    return;
  } else {
    for (int k = i; k < size; ++k) {
      if (sum + arr[k] > multi * arr[k]) {
        sum += arr[k];
        multi *= arr[k];
        ++cnt;
        such(i + 1);
        sum -= arr[k];
        multi /= arr[k];
      } else if (arr[k] == 1) {
        // 由于有序, 且这一次不满足, 但是下一次是1, 下一次肯定满足
        sum += arr[k];
        multi *= arr[k];
        such(i + 1);
        sum -= arr[k];
        multi /= arr[k];
      } else { 
        // 由于有序, 且这一次不满足, 下一次不为1, 后边肯定都不满足
        break;
      }
      // 去重, 标号相同的球一样
      while (k < size - 1 && arr[k] == arr[k + 1]) {
        ++k;
      }
    }
  }
}
int main() {
  sort(arr.begin(), arr.end());
  such(0);
  cout << cnt << endl;
  return 0;
}
#endif

#if 0
/*
  字符串匹配算法
  te?t*.*
  txt12.xls

  返回false
*/

bool isAdapt(const char* s1, const char* s2) {
  if (*s1 == '\0' && *s2 == '\0') {
    return true;
  }
  if (*s1 == '\0' || *s2 == '\0') {
    return false;
  }
  if (*s1 == '*') {
    // 不匹配, 或者匹配1个, 或者匹配多个
    return isAdapt(s1+1, s2) || isAdapt(s1+1, s2+1) || isAdapt(s1, s2+1);
  }
  if (*s1 == '?' || *s1 == *s2) {
    return isAdapt(s1+1, s2+1);
  } else {
    return false;
  }
}

int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    bool ret = isAdapt(s1.c_str(), s2.c_str());
    cout << (ret==true?"true":"false") << endl;
  }
  return 0;
}
#endif
