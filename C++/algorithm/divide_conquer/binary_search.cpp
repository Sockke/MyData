#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
  分治算法, 分而治之, 合并子规模
  分治算法的思想就是, 原问题的规模较大不易求解,
  将原问题的规模划分成一个个的小规模, 对小规模问题进行求解,
  最后合并子规模, 求出原问题的解

  分治算法本质上就是对问题规模的划分, 问题本身不变, 只是规模缩小了而已
*/

/*
  二分查找, 二分查找类似于分治的思想, 将有序数组划分成左右两部分
  将规模缩小, 再进行查找
*/

int divide(int* arr, int left, int right, int data) {
  // 没有找到
  if (left > right) {
    return -1;
  }
  int mid = left + (right - left) / 2;
  if (arr[mid] == data) {
    // 返回最左边的值下标
    while (mid >= 0 && arr[mid] == data) {
      --mid;
    }
    return mid + 1;
  }
  if (arr[mid] > data) { // 在左边
    return divide(arr, left, mid - 1, data);
  } else { // 在右边
    return divide(arr, mid + 1, right, data);
  }
}

int binarySearch(int* arr, int len, int data) {
  return divide(arr, 0, len - 1, data);
}

int main() {
  int arr[] = {1, 3, 5, 5, 5, 7, 9, 12, 18, 21, 29};
  const int len = sizeof(arr) / sizeof(arr[0]);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  int index = binarySearch(arr, len, 5);
  cout << "index:" << index << endl;
  return 0;
}
