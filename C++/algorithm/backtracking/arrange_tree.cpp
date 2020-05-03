#include <iostream>
#include <vector>
using namespace std;

#if 0
/*
  排列树, 有关数列的全排列的算法
  固定一组值, 求另一组值的全排列, 然后依次类推的过程.
  比如说给定一组数据123, 要固定第1个值, 那么第1个值可能为1, 2, 3
  如果固定的是1, 那么对23再进行全排列, 如果固定的是2, 那么对13进行全排列,
  然后以此类推. 最终叶子节点就是一组排列
*/
int arr[] = {1, 2, 3};
const int len = sizeof(arr) / sizeof(arr[0]);

void arrange_tree(int i) {
  if (i == len) { // 打印排列
    for (auto& e : arr) {
      cout << e << " ";
    }
    cout << endl;
    return;
  }
  for (int k = i; k < len; ++k) {
    swap(arr[i], arr[k]); // 在i位置上固定k
    arrange_tree(i + 1);  // 固定下一个位置
    swap(arr[i], arr[k]); // 不在i位置上固定k了
  }
}

int main() {
  arrange_tree(0);
  return 0;
}
#endif

#if 0
/*
  八皇后问题, 在一个8*8的二维数组中总共有8个皇后,
  两个皇后之间不能进行攻击,
  也就是说任意2个皇后不能在同一行, 或者同一列, 或者同一斜线
  求总共有多少种位置排列
*/

// 下标+1代表行数, 值代表列数, 通过全排列可以得到所有的位置排列
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8}; 
const int len = sizeof(arr) / sizeof(arr[0]);
int counts = 0;

// 判断i位置安不安全
bool isSafe(int i) {
  for (int k = 0; k < i; ++k) {
    if (k == i || arr[k] == arr[i] || abs(k - i) == abs(arr[k] - arr[i])) {
      return false;
    }
  }
  return true;
}
void arrange_tree(int i) {
  if (i == len) {
    ++counts;
    for (auto& e : arr) {
      cout << e << " ";
    }
    cout << endl;
    return;
  }
  for (int k = i; k < len; ++k) {
    swap(arr[i], arr[k]);
    // 如果这两个皇后的位置不安全, 就不需要再进行向下排列了
    if (isSafe(i)) {
      arrange_tree(i + 1);
    }
    swap(arr[i], arr[k]);
  }
}

int main() {
  arrange_tree(0);
  cout << "counts: " << counts << endl;
  return 0;
}
#endif

/*
  特殊排列数, 与排列树的思想类似, 
  排列树的排列是通过元素的交换, 而这个排列树的排列是通过枚举来实现
  之所以要枚举是为了解决, 全排列的输出规则, 先输出小数后输出大数
*/
int arr[] = {1, 2, 3};
const int len = sizeof(arr) / sizeof(arr[0]);
bool state[len]; // 枚举时需要记录状态, 已经枚举的就不需要再枚举了
vector<int> aid;

void arrange_tree(int i) {
  if (i == len) {
    for (auto& e : aid) {
      cout << e << " ";
    }
    cout << endl;
    return;
  }
  for (int k = 0; k < len; ++k) {
    if (!state[k]) {
      state[k] = true; // 已经选择
      aid.push_back(arr[k]);
      arrange_tree(i + 1); // 继续排列
      aid.pop_back();
      state[k] = false; // 取消选择
    }
  }
}

int main() {
  arrange_tree(0);
  return 0;
}
