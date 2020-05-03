#include <iostream>
#include <vector>
#include <string>
using namespace std;

#if 0
/*
  给定一个Excel表格中的列名称，返回其相应的列序号。
  A->1
  B->2
  ...
  AA->27
  AB->28
  ...
  
*/

class Solution {
  public:
    /*
       输入: "AB"
       输出: 28
       输入: "ZY"
       输出: 701

       25*26^0+26*26^1
    */
    int titleToNumber(string s) {
      long long sum = 0;
      int len = s.size();
      long long carry=1;
      for (int i = len - 1; i >= 0; --i) {
        sum += (s[i]-'A'+1)*carry;
        carry *= 26;

      } 
      return sum;
    }
    /*
      输入: 28
      输出: "AB"
      输入: 701
      输出: "ZY"

       26^0->A
       26^0+26^1->AA
       26^0+26^1+26^2->AAA
       701%26=25->Y
       701/26=26
   */
    string convertToTitle(int n) {
      int sum = n;
      string tmp;
      while (sum>26) {
        int carry = (sum-1)%26;
        tmp = string(1, ('A'+carry)) + tmp;
        sum = (sum-1)/26;
      }
      tmp = string(1, ('A'+sum-1)) + tmp;
      return tmp;
    }
};


int main() {
  return 0;
}
#endif

#if 0
/*
  rand(5)转换为rand(7)
*/

int rand5() {
  // 0-4
  return rand()%5;
}
int rand25() {
  // 0-4 5-9 10-14 15-19 20-24
  return rand5()*5+rand5();
}
int rand7() {
  int num = 0;
  while (1) {
    num = rand25();
    if (num < 21) {
      break;
    }
  }
  // 0-6
  return num%7;
}

int main() {
  for (int i = 0; i < 10; ++i) {
    cout << rand7() << " ";
  }
  cout << endl;
  return 0;
}
#endif

// 求平均值, 考虑溢出
// 2个数求平均值, 防止溢出a+(b-a)/2
double avg(double* arr, int len) {
  double avg = 0;
  for (int i = 0; i < len; ++i) {
    avg = avg + (arr[i] - avg) / (i+1);
  }
  return avg;
}

// 由于两个数相加: (a^b)+((a&b)<<1)
// 如果除以2,那么: ((a^b)>>1)+(a&b)
int avg(int a, int b) {
  return ((a^b)>>1) + (a&b);
}

int main() {
  double arr[] = {5, 4, 3, 2, 1};
  int len = sizeof(arr) / sizeof(arr[0]);
  double a = avg(arr, len);
  cout << a << endl; 
  return 0;
}
