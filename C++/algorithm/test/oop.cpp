#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
  大数相加
*/

class BigNum {
  public:
    BigNum(const string& s)
      : _str(s)
    {}
    BigNum operator+(const BigNum& num) {
      string lnum(_str);
      string rnum(num._str);
      reverse(lnum.begin(), lnum.end());
      reverse(rnum.begin(), rnum.end());
      int len = lnum.size() > rnum.size() ? lnum.size() : rnum.size();
      string tmp(len+1, '0');
      lnum.resize(len, '0');
      rnum.resize(len, '0');
      int carry = 0;
      for (int i = 0; i < len; ++i) {
        int curnum = (lnum[i]-'0') + (rnum[i]-'0') + carry;
        carry = curnum / 10;
        tmp[i] = curnum % 10 + '0';

      }
      if (carry > 0) {
        tmp[len] = carry + '0';
        return tmp;

      }
      tmp = tmp.substr(0, len);
      reverse(tmp.begin(), tmp.end());
      return BigNum(tmp);

    }
  private:
    friend ostream& operator<<(ostream& os, const BigNum& num);
    string _str;

};

ostream& operator<<(ostream& os, const BigNum& num) {
  os << num._str;
  return os;
}

int main() {
  string lnum, rnum;
  while (cin >> lnum >> rnum) {
    BigNum l(lnum);
    BigNum r(rnum);
    cout << l+r << endl;
  }
  return 0;
}
