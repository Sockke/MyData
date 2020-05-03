#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

#if 0
/*
  3个空瓶子换1瓶汽水, 如果还生2个空瓶子可以先向老板借一瓶
  n个空瓶能喝多少瓶汽水?
*/
int getBottle(int n) {
  int cnt = 0;
  while (n >= 3) {
    cnt += n / 3;
    n = n % 3 + n / 3;
  }
  if (n == 2) {
    ++cnt;
  }
  return cnt;
}

int main() {
  int n = 0;
  while (cin >> n) {
    cout << getBottle(n) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  一块花布条，里面有些图案，另有一块直接可用的小饰条，里面也有一些图案。
  对于给定的花布条和小饰条，计算一下能从花布条中尽可能剪出几块小饰条来呢？ 
  aaaaaa aa
  3

  其实就是找子串的个数
*/
int getCnt(string& s1, string& s2) {
  int cnt = 0;
  int s_pos = 0;
  while (1) {
    size_t cur_pos = s1.find(s2, s_pos);
    if (cur_pos != string::npos) {
      ++cnt;
      s_pos = cur_pos + s2.size();
    } else {
      break;
    }
  }
  return cnt;
}
int main() {
  string s1, s2;
  while (cin >> s1 >> s2) {
    cout << getCnt(s1, s2) << endl;
  }
  return 0;
}
#endif
