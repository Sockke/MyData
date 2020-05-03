#include <iostream>
#include <vector>
using namespace std;

/*
  堆排:
  1. 建堆
  2. 不断取出堆顶, 放到后边

  1. 如果是大根堆, 那么在建堆的时候保证父节点要比孩子节点大, 那么堆顶就是最大值
  不断取出堆顶元素放到后边, 最后数组元素从小到大排序
  2. 如果是小根堆, 那么在建堆的时候保证父节点要比孩子节点小, 那么堆顶就是最小值
  不断取出堆顶元素放到后边, 最后数组元素从大到小排序

  Top K问题:
  1. 如果要从一个数列中找出前10大的数, 那么肯定是建小根堆, 因为要把小元素淘汰掉
  2. 如果要从一个数列中找出前10小的数, 那么肯定是建大根堆, 因为要把大元素淘汰掉
*/

#if 0
void downAdjust(vector<int>& arr, int p, int len) {
  int lchild = p * 2 + 1;
  int rchild = p * 2 + 2;
  int max_idx = p;
  if (lchild < len && arr[lchild] > arr[max_idx]) {
    max_idx = lchild;
  }
  if (rchild < len && arr[rchild] > arr[max_idx]) {
    max_idx = rchild;
  }
  if (max_idx != p) { // 有孩子比父亲大, 需要调整
    swap(arr[p], arr[max_idx]);
    downAdjust(arr, max_idx, len);
  }
}

void heapSort(vector<int>& arr) {
  // 建堆
  int len = arr.size();
  for (int i = len/2; i >= 0; --i) {
    downAdjust(arr, i, len);
  }

  for (int i = len - 1; i > 0; --i) {
    swap(arr[0], arr[i]);
    downAdjust(arr, 0, i);
  }
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
  }
  heapSort(arr);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
#endif

/*
  堆排解决top k问题
*/
void downAdjust(vector<int>& arr, int p, int len) {
  int lchild = p * 2 + 1;
  int rchild = p * 2 + 2;
  int max_idx = p;
  if (lchild < len && arr[lchild] > arr[max_idx]) {
    max_idx = lchild;
  }
  if (rchild < len && arr[rchild] > arr[max_idx]) {
    max_idx = rchild;
  }
  if (max_idx != p) {
    swap(arr[p], arr[max_idx]);
    downAdjust(arr, max_idx, len);
  }
}

void heapSort(vector<int>& arr, int k) {
  int len = arr.size();
  if (len <= k) {
    return;
  }
  // 建堆
  for (int i = k/2; i >= 0; --i) {
    downAdjust(arr, i, k);
  }
  // 寻找top k
  for (int i = len - 1; i >= k; --i) {
    if (arr[i] < arr[0]) {
      swap(arr[0], arr[i]);
      downAdjust(arr, 0, k);
    }
  }
}

int main() {
  // 寻找前k小的元素
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
  }
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  heapSort(arr, 5);
  for (int i = 0; i < 5; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;
  return 0;
}
