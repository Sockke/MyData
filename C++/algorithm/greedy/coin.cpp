#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
  贪心算法:
  具有最优子结构的问题, 并且最优子结构是确定的, 可以使用贪心算法
  1. 对所确定的最优子结构数据进行排序
  2. 顺序判断, 选择最优子结构
*/

#if 0
/*
  硬币问题:
  给定一组硬币的面额以及一个数字, 求利用给定面额组成该数字所需要硬币的最少数量
*/

int main() {
  int num = 11;
  vector<int> coins{1, 3, 5};
  // 排序
  sort(coins.begin(), coins.end(), greater<int>());

  int i = 0;
  int amount = 0;
  while(num) {
    if (num >= coins[i]) {
      num -= coins[i];
      ++amount;
    } else {
      ++i; 
    }
  }

  cout << amount << endl;

  return 0;
}
#endif

/*
  01部分背包问题:
  给定一个背包, 以及一组物品, 物品可以部分装入, 求把背包装满后物品的最大价值为多少
*/

struct Goods {
  double unit_price() const {
    return v * 1.0 / w;
  }
  bool operator>(const Goods& goods) const {
    return unit_price() > goods.unit_price();
  }
  int id;
  int w;
  int v;
};

int main() {
  vector<int> W{8, 6, 4, 2, 5};
  vector<int> V{6, 4, 7, 8, 6};
  int N = 12;
  const int size = W.size();

  // 最优子结构就是最高的性价比
  // 排序
  vector<Goods> goods(size);
  for (int i = 0; i < size; ++i) {
    goods[i].id = i;
    goods[i].w = W[i];
    goods[i].v = V[i];
  }
  sort(goods.begin(), goods.end(), [](const Goods& l, const Goods& r)->bool{
    return l > r;
  });

  int i = 0;
  double max_value = 0;
  while (N) {
    if (N >= goods[i].w) {
      max_value += goods[i].v * 1.0; 
      N -= goods[i].w;
      ++i;
    } else {
      max_value += goods[i].unit_price() * N; 
      break;
    }
  }

  cout << max_value << endl;

  return 0;
}
