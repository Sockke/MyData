#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;
#if 0
/*
  子集树, 将一个数列抽象成一个二叉树, 
  向左子树走的路径为1, 代表选择
  向右子树走的路径为0, 代表不选择
  最终通过判断从根节点到每个叶子节点的路径情况, 来确定该数列的子集
*/

int arr[] = {1, 2, 3};
const int len = sizeof(arr) / sizeof(arr[0]);
int aid[len] = {0}; // 辅助数组

void subset_tree(int i) {
  if (i == len) { 
    for (int k = 0; k < len; ++k) {
      if (aid[k] == 1)  {
        cout << arr[k] << " ";
      }
    }
    cout << endl;
    return;
  }
  aid[i] = 1; // 选择
  subset_tree(i + 1);
  aid[i] = 0; // 不选择
  subset_tree(i + 1);
}

int main() {
  subset_tree(0); // 从下标为0的元素开始, 抽象成子集树后, i代表层数
  return 0;
}
#endif

#if 0
/*
  整数选择问题:
  给定一组整数, 从中挑选一部分整数, 使得挑选的整数的和与剩下整数的和的差值最小
  打印挑选的整数

  因为要挑选的整数的数量不一定, 因此无法进行剪枝操作
*/
int arr[] = {12, 6, 7, 11, 16, 3, 8};
const int len = sizeof(arr) / sizeof(arr[0]);
vector<int> aid; // 辅助数组
int has_select = 0; // 已经选择的整数和
int no_select = 0; // 没有选择的整数和
int gap = INT_MAX; // 最小的差值
vector<int> result;

void selectInt(int i) {
  if (i == len) {
    int cur_cap = abs(has_select - no_select);
    if (cur_cap < gap) {
      gap = cur_cap;
      result = aid;
    }
    return;
  }
  has_select += arr[i];
  no_select -= arr[i];
  aid.push_back(arr[i]); //aid[i] = 1;
  selectInt(i + 1);
  has_select -= arr[i];
  no_select += arr[i];
  aid.pop_back(); //aid[i] = 0;
  selectInt(i + 1);
}

int main() {
  for (auto& e : arr) {
    no_select += e;
  }
  selectInt(0);
  cout << gap << endl;
  for (auto& e : result) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
#endif

#if 0
/*
  挑选整数问题:
  给定2n个整数, 挑选n个整数, 使得挑选的n个整数和与剩下的n个整数和的差值最小
*/
int arr[] = {12, 6, 7, 11, 16, 3, 8, 4};
const int len = sizeof(arr) / sizeof(arr[0]);
vector<int> aid;
int has_select = 0;
int no_select = 0;
int gap = INT_MAX;
vector<int> result;
int counts = 0;

void selectInt(int i) {
  if (i == len) {
    ++counts;
    if (aid.size() != len / 2) {
      return; 
    }
    int cur_cap = abs(has_select - no_select);
    if (cur_cap < gap) {
      gap = cur_cap;
      result = aid;
    }
    return;
  }
  // 如果已经挑选了n个了, 就不需要再挑选了
  if (aid.size() < len / 2) {
    has_select += arr[i];
    no_select -= arr[i];
    aid.push_back(arr[i]); //aid[i] = 1;
    selectInt(i + 1);
    has_select -= arr[i];
    no_select += arr[i];
    aid.pop_back(); //aid[i] = 0;
  }
  // 如果已选择的个数与剩下未处理的整数个数的和不足n, 就不需要再挑选了
  int no_process_num = len - i - 1;
  if (aid.size() + no_process_num >= len / 2) {
    selectInt(i + 1);
  }
}

int main() {
  for (auto& e : arr) {
    no_select += e;
  }
  selectInt(0);
  cout << gap << endl;
  for (auto& e : result) {
    cout << e << " ";
  }
  cout << endl;
  cout << counts << endl;
  return 0;
}
#endif

#if 0
/*
  挑选数字问题:
  给定一组整数和一个数字, 挑选一部分整数, 使得整数的和正好与这个数字相等
*/
int arr[] = {4, 8, 12, 16, 7, 9, 3};
const int len = sizeof(arr) / sizeof(arr[0]);
vector<int> aid;
int num = 18;
int has_select = 0;
vector<int> result;
int counts = 0;


void selectInt(int i) {
  if (i == len) {
    ++counts;
    if (has_select == num) {
      result = aid; 
    }
    return;
  }
  // 如果已经挑选的整数和已经大于num, 就不需要再挑选了
  if (has_select + arr[i] <= num) {
    has_select += arr[i];
    aid.push_back(arr[i]);
    selectInt(i + 1);
    has_select -= arr[i];
    aid.pop_back();
  }
  // 如果已经挑选的和与剩余未处理整数的和加起来还不足num, 那就不需要挑选了
  int sum = 0; // 未处理的整数和
  for (int k = i + 1; k < len; ++k) {
    sum += arr[k];
  }
  if (has_select + sum >= num) {
    selectInt(i + 1);
  }
}

int main() {
  selectInt(0);
  for (auto& e : result) {
    cout << e << " ";
  }
  cout << endl;
  cout << counts << endl;
  return 0;
}
#endif

/*
  穷举法类似于子集树算法, 也是关注子集问题的算法.
  但是穷举法并不是通过判断从根节点到叶子节点的路径,
  而是在穷举的过程中来组合不同的子集

  穷举法是一个多阶树, 要比子集树的高度要低, 算法的效率相对来说比子集树要好
  穷举法一般应用于这种场景, 比如说组合一个特定值(尤其是允许重复选择的场景)
*/
/*
  给定一组整数和一个数字, 选择一部分整数, 使得选择的整数的和等于这个数字
*/
int arr[] = {4, 8, 12, 16, 7, 9, 3};
const int len = sizeof(arr) / sizeof(arr[0]);
vector<int> aid; // 辅助数组
int num = 18;
void exhaustion(int i, int left_num) {
  if (left_num== 0) { // 选择的整数和刚好等于这个数字
    for (auto& e : aid) {
      cout << e << " ";
    }
    cout << endl;
    return;
  }
  for (int k = i; k < len; ++k) {
    // 如果当前数大于剩余的数, 就不能进行相减了
    if (left_num >= arr[k]) {
      aid.push_back(arr[k]);
      exhaustion(k + 1, left_num - arr[k]); // 继续穷举, 不允许重复选择
      //exhaustion(k, left_num - arr[k]); // 可以重复选择
      aid.pop_back();
    }
  }
}
int main() {
  exhaustion(0, num);
  return 0;
}
