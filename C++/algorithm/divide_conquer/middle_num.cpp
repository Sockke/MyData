#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
  给定2个有序的数组, 找这2个数组合并之后的中位数
  规定时间复杂度为O(logN)

  采用二分搜索的思想.
  虽然是2个有序的数组, 但是可以将这2个数组看成一个整体.
  1. 将这2个数组都分成2部分, 左边的个数是总数的一半,
  2. 并且使得左边的所有数都小于右边的所有数.
  满足这2个特点, 这样两个数组的分界值就能确定中位数的大小 
*/

double find_middle_num(vector<int>& arr1, vector<int>& arr2) {
  int len1 = arr1.size();
  int len2 = arr2.size();
  // 有一个数组可能为空
  if (len1 == 0) {
    int mid = (len2 - 1) / 2;
    if (len2 % 2 == 0) {
      return (arr2[mid] + arr2[mid+1]) * 1.0 / 2;
    } else {
      return arr2[mid];
    }
  } else if (len2 == 0) {
    int mid = (len1 - 1) / 2;
    if (len1 % 2 == 0) {
      return (arr1[mid] + arr1[mid+1]) * 1.0 / 2;
    } else {
      return arr1[mid];
    }
  }
  // 二分法
  int left = 0;
  int right = len1 - 1;
  int k = (len1 + len2 + 1) / 2; // 中位数在第k个
  int k1 = 0, k2 = 0; // arr1中前k1个, arr2中前k2个
  while (left <= right) {
    k1 = left + (right - left) / 2 + 1;
    k2 = k - k1;
    if (k1 > 0 && k2 < len2 && arr1[k1 - 1] > arr2[k2]) {
      // 左边有偏大的数
      right = k1 - 2; 
    } else if (k2 > 0 && k1 < len1 && arr2[k2 - 1] > arr1[k1]) {
      // 左边有偏小的数
      left = k1;
    } else {
      break;
    }
  }
  // 考虑中位数都在某一个数组的情况
  int mid_num1 = 0, mid_num2 = 0;
  if (k1 == 0) { // 中位数在arr2中
    mid_num1 = arr2[k2 - 1];
  } else if (k2 == 0) {  // 中位数在arr1中
    mid_num1 = arr1[k1 - 1];
  } else { // 可能在arr1中, 也可能在arr2中
    mid_num1 = max(arr1[k1 - 1], arr2[k2 - 1]);
  }
  // 如果存在第二个中位数
  if (k1 == len1) { // 第二个中位数在arr2中
    mid_num2 = arr2[k2];
  } else if (k2 == len2) { // 第二个中位数在arr1中
    mid_num2 = arr1[k1];
  } else { // 可能在arr1中, 也可能在arr2中
    mid_num2 = min(arr1[k1], arr2[k2]);
  }
  // 判断奇偶性 
  if ((len1 + len2) % 2 == 0) { // 偶数
    return (mid_num1 + mid_num2) * 1.0 / 2;
  } else {
    return mid_num1;
  }
}

int main() {
  vector<int> arr1;
  vector<int> arr2;
  vector<int> arr;
  for (int i = 0; i < 9; ++i) {
    arr1.push_back(rand() % 100);
  }
  for (int i = 0; i < 6; ++i) {
    arr2.push_back(rand() % 100);
  }
  sort(arr1.begin(), arr1.end());
  sort(arr2.begin(), arr2.end());
  arr = arr1;
  for (auto& e : arr2) {
    arr.push_back(e);
  }
  sort(arr.begin(), arr.end());

  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;

  double mid_num = find_middle_num(arr1, arr2);

  cout << mid_num << endl;

  return 0;
}

