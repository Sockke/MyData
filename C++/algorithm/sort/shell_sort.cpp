#include <iostream>
#include <vector>
using namespace std;

/*
  希尔排序:
  本质上是分组进行插入排序, 对插入排序的一种优化
  
  1. 先让元素两两一组, 进行插入排序
  2. 然后再让元素四四一组, 进行插入排序, 以此类推
  3. 当变成1个组时, 排序完毕
*/

void shellSort(vector<int>& arr) {
  int len = arr.size();
  int group = len;
  while (group > 1) {
    group /= 2;
    for (int k = 0; k < group; ++k) {
      // 进行插入排序
      for (int i = k + group; i < len; i += group) {
        int insert_num = arr[i];
        int j = i - group;
        for (; j >= 0; j -= group) {
          if (insert_num < arr[j]) {
            arr[j + group] = arr[j];
          } else {
            break;
          }
        }
        arr[j + group] = insert_num;
      }
    }
  }
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
  }
  shellSort(arr);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
