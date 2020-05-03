
#if 0
/*
  洗牌在生活中十分常见，现在需要写一个程序模拟洗牌的过程。 现在需要洗2n张牌，
  从上到下依次是第1张，第2张，第3张一直到第2n张。首先，我们把这2n张牌分成两堆，
  左手拿着第1张到第n张（上半堆），右手拿着第n+1张到第2n张（下半堆）。
  接着就开始洗牌的过程，先放下右手的最后一张牌，再放下左手的最后一张牌，
  接着放下右手的倒数第二张牌，再放下左手的倒数第二张牌，直到最后放下左手的第一张牌。
  接着把牌合并起来就可以了。 例如有6张牌，最开始牌的序列是1,2,3,4,5,6。首先分成两组，
  左手拿着1,2,3；右手拿着4,5,6。在洗牌过程中按顺序放下了6,3,5,2,4,1。
  把这六张牌再次合成一组牌之后，我们按照从上往下的顺序看这组牌，
  就变成了序列1,4,2,5,3,6。 现在给出一个原始牌组，请输出这副牌洗牌k次之后从上往下的序列。

  有T组数据, 2*n张牌, 需要洗k次, 求洗牌后的牌序, 输出结尾不能有多余空格
*/

void shuffle(vector<int>& cards) {
  int size = cards.size();
  vector<int> tmp(size);
  int l1 = 0;
  int l2 = size / 2;
  int i = 0;
  while (l1 < size / 2 && l2 < size) {
    tmp[i++] = cards[l1];
    tmp[i++] = cards[l2];
    ++l1;
    ++l2;
  }
  cards = tmp;
}

int main() {
  int T = 0; // T组数据
  cin >> T;
  while (T--) {
    int n = 0, k = 0; // 2n张牌, 洗k次
    cin >> n >> k;
    vector<int> cards(2 * n);
    for (int i = 0; i < 2*n; ++i) {
      cin >> cards[i];
    }
    while (k--) {
      shuffle(cards);
    }
    for (int i = 0; i < 2*n; ++i) {
      if (i == 2*n-1) {
        cout << cards[i];
        continue;
      }
      cout << cards[i] << " ";
    }
    cout << endl;
  }
}
#endif

#if 0
/*
  MP3光标位置, 有n个歌曲, U向上移动光标, D向下移动光标
  假设10首歌曲:
  特殊翻页: 当前页面: 1 2 3 4, 光标指向1, 
  U向上移动光标, 变成7 8 9 10, 光标指向10
  D向下移动光标, 变成1 2 3 4, 光标指向1.
  普通翻页:
  4 5 6 7, 光标指向4, U向上移动, 变成3 4 5 6, 光标指向3
  4 5 6 7, 光标指向7, D向下移动, 变成5 6 7 8, 光标指向8
*/

int func(vector<int>& arr, int n, string command) {
  int list_len = min(4, n); // 考虑n<4的情况
  int beg = 0; // 当前页面起始位置
  int i = 0; // 光标在当前页面的偏移
  for (auto& e : command) {
    if (e == 'U') {
      if (beg == 0 && i == 0) {
        i = list_len-1;
        beg = n - list_len;
      } else {
        if (i == 0) {
          --beg;
        } else {
          --i;
        }
      }
    } else {
      if (beg == n - list_len && i == list_len-1) {
        i = 0;
        beg = 0;
      } else {
        if (i == list_len-1) {
          ++beg;
        } else {
          ++i;
        }
      }
    }
  }
  for (int i = 0; i < list_len; ++i) {
    arr.push_back((beg+i)%n+1);
  }
  return beg+1+i;
}

int main() {
  int n = 0;
  string command;
  while (cin >> n >> command) {
    vector<int> arr;
    int cur = func(arr, n, command);
    for (auto& e : arr) {
      cout << e << " ";
    }
    cout << endl;
    cout << cur << endl;
  }
  return 0;
}
#endif

#if 0
/*
  找到数组中出现次数超过总数一半的数字,
  找不到返回0
*/

class Gift {
  public:
    int getValue(vector<int> gifts, int n) {
      sort(gifts.begin(), gifts.end());
      int mid = n / 2;
      int left = mid-1, right = mid+1;
      int cnt = 0;
      while (left >= 0 && right < n) {
        if (gifts[left--] == gifts[mid]) {
          ++cnt;
        }
        if (gifts[right++] == gifts[mid]) {
          ++cnt;
        }
      }
      while (left >= 0) {
        if (gifts[left--] == gifts[mid]) {
          ++cnt;
        }
      }
      while (right < n) {
        if (gifts[right++] == gifts[mid]) {
          ++cnt;
        }
      }
      if (cnt > n/2) {
        return gifts[mid];
      } else {
        return 0;
      }
    }
};
#endif

#if 0
/*
  不能使用+, -, *, /. 来计算两个数的加法
  采用位运算来解决
*/
class Solution {
  public:
    int Add(int num1, int num2)
    {
      while (num2) {
        int num = num1 ^ num2; // 不进位的值
        int carry = (num1 & num2) << 1; // 需要进的位
        num1 = num;
        num2 = carry;
      }
      return num1;
    }
};
#endif

#if 0
class Solution {
  public:
    /**
     *  奇数位上都是奇数或者偶数位上都是偶数
     *  输入：数组arr，长度大于2
     *  len：arr的长度
     *  将arr调整成奇数位上都是奇数或者偶数位上都是偶数
     
     思路就是用两个下标, 分别指向偶数位与奇数位, 然后将最后一个数据往指定位放
     */
    void oddInOddEvenInEven(vector<int>& arr, int len) {
      int i = 0, j = 1;
      while (i < len && j < len) {
        if (arr[len - 1] % 2 == 0) {
          // 偶数
          swap(arr[i], arr[len - 1]);
          i += 2;
        } else {
          // 奇数
          swap(arr[j], arr[len - 1]);
          j += 2;
        }
      }
    }
};
#endif

#if 0
/*
  NowCoder号称自己已经记住了1-100000之间所有的斐波那契数。
   为了考验他，我们随便出一个数n，让他说出第n个斐波那契数。
   当然，斐波那契数会很大。因此，如果第n个斐波那契数不到6位，则说出该数；否则只说出最后6位。
*/
int arr[100001] = {1, 1};
void init() {
  // fibonaaci后边的数字会很大, 在存储的时候就直接按6位存就好了
  for (int i = 2; i <= 100000; ++i) {
    arr[i] = (arr[i-2]+arr[i-1])%1000000;
  }
}
int main() {
  init();
  int n = 0;
  while (cin >> n) {
    if (n < 25) { // n=25是第1个超过6位数的fibonacci数
      printf("%d\n", arr[n]);
    } else {  // 考虑低6位起始为0的情况, 要补0
      printf("%06d\n", arr[n]);
    }
  }
  return 0;
}
#endif

#if 0
/*
  输入有多组数据，每组数据有两行。第一行抄送列表，姓名之间用一个逗号隔开。
  如果姓名中包含空格或逗号，则姓名包含在双引号里。总长度不超过512个字符。
  第二行只包含一个姓名，是待查找的用户的名字（姓名要完全匹配）。长度不超过16个字符

  "Letendre, Bruce",Joe,"Quan, William"
  William
  -> Important!
  "Letendre, Bruce",Joe,"Quan, William"
  Quan, William
  ->Ignore
*/
bool func(string& s1, string& s2) {
  int len = s1.size();
  for (int i = 0; i < len; ++i) {
    string tmp;
    if (s1[i] == '"') {
      ++i;
      while (i < len && s1[i] != '"') {
        tmp += s1[i];
        ++i;
      }
      if (tmp == s2) {
        return true;
      }
    } else if (s1[i] != ',') {
      while (i < len && s1[i] != ',') {
        tmp += s1[i];
        ++i;
      }
      if (tmp == s2) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  string s1, s2;
  while (getline(cin, s1)) {
    getline(cin, s2);
    bool ret = func(s1, s2);
    if (ret) {
      cout << "Ignore" << endl;
    } else {
      cout << "Important!" << endl;
    }
  }
  return 0;
}
#endif

#if 0
/*
  有两个32位整数n和m，请编写算法将m的二进制数位插入到n的二进制的第j到第i位,
  其中二进制的位数从低位数到高位且以0开始。
  给定两个数int n和int m，同时给定int j和int i，意义如题所述，请返回操作后的数，
  保证n的第j到第i位均为零，且m的二进制位数小于等于i-j+1。
*/
class BinInsert {
  public:
    int binInsert(int n, int m, int j, int i) {
      // write code here
      return n|(m << j);
    }

};
#endif

