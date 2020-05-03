#include <iostream>
#include <vector>
using namespace std;

#if 0
/*
  今年公司年会的奖品特别给力，但获奖的规矩却很奇葩：
  1. 首先，所有人员都将一张写有自己名字的字条放入抽奖箱中；
  2. 待所有字条加入完毕，每人从箱中取一个字条；
  3. 如果抽到的字条上写的就是自己的名字，那么“恭喜你，中奖了！”
  现在告诉你参加晚会的人数，请你计算有多少概率会出现无人获奖？

  错排公式：f(n) = (n-1)*(f(n-1)+f(n-2))
  错排公式用于, n本书中每一本书都不能放在原来自己的位置上, 求有多少种排列方式
  推导:
  1. 取出第i本书, 放置到除了i的其他位置, 将该位置的书拿走准备放置到新的位置, 有n-1种放法
  2. 如果放置到第i个位置, 那么就是两本书位置互换, 对剩余n-2本书再进行错排, (n-1)*f(n-2)
  3. 如果放置到除了i其他位置上, 那么继续对剩下的n-1本书进行错排, (n-1)*f(n-1)
  因此总共有f(n) = (n-1)*f(n-2)+(n-1)*f(n-1) = (n-1)*(f(n-2)+f(n-1))种

*/
int main() {
  int n = 0;
  long long arr[21] = {0, 0, 1};
  for (int i = 3; i <= 20; ++i) {
    arr[i] = (i-1)*(arr[i-2]+arr[i-1]);
  }
  while (cin >> n) {
    long long all = 1;
    for (int i = 1; i <= n; ++i) {
      all *= i;
    }
    printf("%.2lf%%\n", arr[n]*100.0/all);
  }
  return 0;
}
#endif

#if 0
/*
  和中国的节日不同，美国的节假日通常是选择某个月的第几个星期几这种形式，因此每一年的放假日期都不相同。具体规则如下：
  1月1日：元旦
  1月的第三个星期一：马丁·路德·金纪念日
  2月的第三个星期一：总统节
  5月的最后一个星期一：阵亡将士纪念日
  7月4日：美国国庆
  9月的第一个星期一：劳动节
  11月的第四个星期四：感恩节
  12月25日：圣诞节
  现在给出一个年份，请你帮忙生成当年节日的日期。

  蔡勒公式: 计算星期几
  date = (d + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400)%7
  其中d为几号, m为几月, y为年
  其中m的取值[3,14], 当m=1时, 是去年的13月, 当m=2时, 是去年的14月
  计算出来的date+1为当前的日期
*/
int Date(int year, int month, int n, int date) {
  int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int y = year;
  if ((year % 400 == 0) || (year % 100 && year % 4 != 0)) {
    ++days[1];
  }
  int m = month;
  if (month == 1 || month == 2) {
    m += 12;
    --y;
  }
  int d = 1;
  int day = 0;
  int cur_date = 0;
  while (d <= days[(month-1)%12] && n > 0) {
    cur_date = (d + 2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    if (cur_date+1 == date) {
      day = d;
      --n;
    }
    ++d;
  }
  return day;
}

int main() {
  int y;  
  while (cin>>y){ 
    cout<<y<<"-01-01"<<endl; 
    printf("%d-01-%02d\n",y,Date(y,1,3,1)); 
    printf("%d-02-%02d\n",y,Date(y,2,3,1)); 
    printf("%d-05-%02d\n",y,Date(y,5,10,1));
    cout<<y<<"-07-04"<<endl; 
    printf("%d-09-%02d\n",y,Date(y,9,1,1)); 
    printf("%d-11-%02d\n",y,Date(y,11,4,4)); 
    cout<<y<<"-12-25"<<endl<<endl;
  }
  return 0;
}
#endif

#if 0
/*
  数根:
  比如，对于24 来说，把2 和4 相加得到6，由于6 是一位数，因此6 是24 的数根。
  再比如39，把3 和9 加起来得到12，由于12 不是一位数，因此还得把1 和2 加起来，
  最后得到3，这是一个一位数，因此3 是39 的数根。
  现在给你一个正整数，输出它的数根。
*/
int shugen(int n) {
  if (n <= 9) {
    return n;
  } else {
    long long sum = 0;
    while (n) {
      sum += (n%10);
      n /= 10;
    }
    return shugen(sum);
  }
}
int main() {
  string s;
  while (cin >> s) {
    int sum = 0;
    for (auto& e : s) {
      sum += (e-'0');
    }
    cout << shugen(sum) << endl;
  }
  return 0;
}
#endif

#if 0
/*
    第一个猴子来了，它把桃子分成五堆，五堆一样多，但还多出一个。
    它把剩下的一个留给老猴子，自己拿走其中的一堆。
    第二个猴子来了，它把桃子分成五堆，五堆一样多，但又多出一个。
    它把多出的一个留给老猴子，自己拿走其中的一堆。
    后来的小猴子都如此照办。最后剩下的桃子全部留给老猴子。
    这里有n只小猴子，请你写个程序计算一下在开始时至少有多少个桃子，
    以及最后老猴子最少能得到几个桃子。
    n = 5 -> 3121 1025
    n = 1 -> 1 1

    数学问题, 设一开始有a个桃子.
    n1 = 4/5(a-1)
    n2 = 4/5(n1-1)
    ...
    nn = (4/5)^n * a - ((4/5)^n+(4/5)^(n-1)...+(4/5))
    = (4/5)^n*(a + 4) - 4
    nn为最后一个小猴子拿走的桃子数, 只要保证nn为整数即可
    而老猴子拿走的桃子数b = nn + n
*/
int main() {
  int n = 0;
  while (cin >> n) {
    if (n == 0) {
      break;
    }
    cout << (long long)pow(5, n) - 4 << " " << (long long)pow(4, n) + n - 4 << endl;
  }
  return 0;
}
#endif

#if 0
/*
  居然有假币！ 现在猪肉涨了，但是农民的工资却不见涨啊，没钱怎么买猪肉啊。
  nowcoder这就去买猪肉，结果找来的零钱中有假币！！！可惜nowcoder
  一不小心把它混进了一堆真币里面去了。只知道假币的重量比真币的质量要轻，
  给你一个天平（天平两端能容纳无限个硬币），请用最快的时间把那个可恶的假币找出来。

  找规律, 每次尽量平均分成3份, a a b, 使得a最小要大于等b
  先拿a a来称, 运气不好, 假币肯定在较多的a堆里
  因此在拿a来尽量平均分成3份, 以此类推
*/
int getCnt(int n) {
  if (n <= 3) {
    return n/2;
  }
  int cnt = 1;
  while (n > 3) {
    ++cnt;
    // 保证分成的a a b三份, a >= b
    if (n % 3 != 0) {
      n = n / 3 + 1;
    } else {
      n = n / 3;
    }
  }
  return cnt;
}
int main() {
  int n = 0;
  while (cin >> n) {
    if (n == 0) {
      break;
    }
    cout << getCnt(n) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  一个正整数可以分解成一个或多个数组的积。例如36=2*2*3*3，即包含2和3两个因子。
  NowCoder最近在研究因子个数的分布规律，现在给出一系列正整数，
  他希望你开发一个程序输出每个正整数的因子个数。

  将一个数尽可能的分解成很多因子相乘, 求里面不重复因子的个数
*/
int factors(int n) {
  if (n == 2) {
    return 1;
  }
  int cnt = 0;
  for (int i = 2; i <= sqrt(n); ++i) {
    if (n % i == 0) {
      ++cnt;
    }
    while (n % i == 0) {
      n /= i;
    }
  }
  // 如果n>1, 说明有大于sqrt(n)的因子
  if (n != 1) {
    ++cnt;
  }
  return cnt;
}

int main() {
  int n = 0;
  while (cin >> n) {
    cout << factors(n) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  所谓因子分解，就是把给定的正整数a，分解成若干个素数的乘积，即 a = a1 × a2 × a3 × ... × an,并且 1 < a1
  ≤ a2 ≤ a3 ≤ ... ≤ an。其中a1、a2、...、an均为素数。  先给出一个整数a，请输出分解后的因子。
*/
void getFactor(int n, vector<int>& factors) {
  for (int i = 2; i <= n; ++i) {
    while (n % i == 0) {
      factors.push_back(i);
      n /= i;
    }
  }
}

int main() {
  int n = 0;
  while (cin >> n) {
    vector<int> factors;
    getFactor(n, factors);
    int len = factors.size();
    cout << n << " = ";
    for (int i = 0; i < len - 1; ++i) {
      cout << factors[i] << " * ";
    }
    if (len > 0) {
      cout << factors[len-1] << endl;
    }
  }
  return 0;
}
#endif

#if 0
/*
  |1 1|^2 => |1 1| * |1 1| => |2 1|
  |1 0|      |1 0|   |1 0|    |1 1|

  |1 1|^n => ...
  |1 0|

  m代表对应的个数, m[i]代表n的大小, 矩阵的n次方后左上角的值为密码 
  密码为4位数, 不足补零, 超过取低4位
  输入有多组数据。
  每组数据两行：第一行包含一个整数n (1≤n≤100)；第二行包含n个正整数Xi (1≤Xi≤10000)
*/
// 1 2 3 5 8 ... fibonacci数列
vector<int> fibo({1, 1});
void init_fibo() {
  for (int i = 2; i <= 10000; ++i) {
    int num = fibo[i-1] + fibo[i-2];
    fibo.push_back(num % 10000);
  }
}
int main() {
  int m = 0;
  while (cin >> m) {
    vector<int> nums(m, 0);
    for (int i = 0; i < m; ++i) {
      cin >> nums[i];
    }
    init_fibo();
    for (auto& e : nums) {
      printf("%04d", fibo[e]);
    }
    cout << endl;
  }
  return 0;
}
#endif

#if 0
/*
  NowCoder开了一家早餐店，这家店的客人都有个奇怪的癖好：他们只要来这家店吃过一次早餐，
  就会每天都过来；并且，所有人在这家店吃了两天早餐后，接下来每天都会带一位新朋友一起来品尝。
  于是，这家店的客人从最初一个人发展成浩浩荡荡成百上千人：1、1、2、3、5……
  现在，NowCoder想请你帮忙统计一下，某一段时间范围那他总共卖出多少份早餐（假设每位客人只吃一份早餐）

  fibonacci数列
*/
long long arr[81] = {0, 1, 1};
void init() {
  for (int i = 3; i <= 80; ++i) {
    arr[i] = arr[i-2] + arr[i-1];
  }
}
long long getCnt(int beg, int end) {
  long long sum = 0;
  for (int i = beg; i <= end; ++i) {
    sum += arr[i];
  }
  return sum;
}
int main() {
  init();
  int beg, end;
  while (cin >> beg >> end) {
    cout << getCnt(beg, end) << endl;
  }
  return 0;
}
#endif

#if 0
/*
  一只成熟的兔子每天能产下一胎兔子。每只小兔子的成熟期是一天。 
  某人领养了一只小兔子，请问第N天以后，他将会得到多少只兔子。 
  测试数据包括多组，每组一行，为整数n(1≤n≤90)。
  1->1
  2->2
  Fibonacci数列
*/
long long arr[91] = {1, 1, 2};
void init()  {
  for (int i = 2; i <= 90; ++i) {
    arr[i] = arr[i-2] + arr[i-1];
  }
}
int main() {
  init();
  int n = 0;
  while (cin >> n) {
    cout << arr[n] << endl;
  }
  return 0;
}
#endif
