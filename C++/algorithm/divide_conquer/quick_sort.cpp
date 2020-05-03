#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
  快速排序, 找基准值位置的过程.
  快排是基于分治的算法思想, 每次将第一个值作为基准值, 确定它在有序数列中的位置,
  该基准值的左边都比他小, 右边都比他大, 然后划分成左右两个数列, 继续进行快排.

  平均的时间复杂度为O(NlogN), 找基准值的位置为O(N), 分治为O(logN)
  但是如果数列趋于有序, 那么普通的快排时间时间复杂度会趋于O(N*N)
  这是因为基准值的位置总是在数列的两端, 导致划分不均匀, 甚至划分成链表结构
  因此需要在选择基准值上做一定优化, 比如说三位取中
*/

#if 0
int partition(int* arr, int left, int right) {
  int data = arr[left];
  while (left < right) {
    while (left < right && arr[right] > data) {
      --right;
    }
    if (left < right) {
      arr[left] = arr[right];
      ++left;
    }
    while (left < right && arr[left] <= data) {
      ++left;
    }
    if (left < right) {
      arr[right] = arr[left];
      --right;
    }
  }
  arr[left] = data; // 把基准值填进去
  return left;
}

void divide(int* arr, int left, int right) {
  if (left > right) {
    return;
  }
  int pos = partition(arr, left, right);
  divide(arr, left, pos - 1);
  divide(arr, pos + 1, right);
}

void quickSort(int* arr, int len) {
  divide(arr, 0, len - 1);
}

int main() {
  int arr[20] = {0};
  const int len = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len; ++i) {
    arr[i] = rand() % 100;
  }
  quickSort(arr, len);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
#endif


/*
  用快排来解决topK问题
  快排每一次都能够确定一个基准值在有序数列中的位置, 使得基准值左边的数都比它小,
  右边的数都比它大, 很适合去求解第topK, 或者前topK的问题
  但是如果数列趋于有序, 还需要在快排上做优化, 平均时间复杂度为NlogN, 最坏为N*N

  解决topK问题还可以通过优先级队列来实现, 底层就是大根堆和小根堆的结构
  ...
*/
int partition(vector<int>& arr, int left, int right) {
  int data = arr[left];
  while (left < right) {
    while (left < right && arr[right] > data) {
      --right;
    }
    if (left < right) {
      arr[left] = arr[right];
      ++left;
    }
    while (left < right && arr[left] <= data) {
      ++left;
    }
    if (left < right) {
      arr[right] = arr[left];
      --right;
    }
  }
  arr[left] = data;
  return left;
}

int max_divide(vector<int>& arr, int left, int right, int k) {
  if (left > right) {
    return -1;
  }
  int pos = partition(arr, left, right);
  int len = arr.size();
  if (len - pos == k) { // 第k大
    return pos;
  }
  if (len - pos > k) { // pos偏小, 向右找
    return max_divide(arr, pos + 1, right, k);
  } else { // pos偏大, 向左找
    return max_divide(arr, left, pos - 1, k);
  }
}

int max_topK_num(vector<int>& arr, int k) {
  return max_divide(arr, 0, arr.size() - 1, k);
}

int min_divide(vector<int>& arr, int left, int right, int k) {
  if (left > right) {
    return -1;
  }
  int pos = partition(arr, left, right);
  if (pos + 1 == k) {
    return pos;
  }
  if (pos + 1 > k) { // pos偏大, 在左边
    return min_divide(arr, left, pos - 1, k);
  } else { // pos偏小, 在右边
    return min_divide(arr, pos + 1, right, k);
  }
}

int min_topK_num(vector<int>& arr, int k) {
  return min_divide(arr, 0, arr.size() - 1, k);
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
    cout << arr[i] << " ";
  }
  cout << endl;
  // 第topK问题
  int pos = max_topK_num(arr, 5);
  cout << "第k大的数:" << arr[pos] << endl;
  cout << "前k大的数:";
  for (int i = pos; i < 20; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;

  pos = min_topK_num(arr, 5);
  cout << "第k小的数:" << arr[pos] << endl;
  cout << "前k小的数:";
  for (int i = 0; i <= pos; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;

  sort(arr.begin(), arr.end());
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
