#include <iostream>
#include <vector>
using namespace std;

// 冒泡排序
void bubbleSort(vector<int>& arr) {
  int len = arr.size();
  for (int i = len - 1; i > 0; --i) {
    bool is_swap = false;
    for (int j = 0; j < i; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        is_swap = true;
      }
    }
    if (!is_swap) {
      break;
    }
  }
}

// 选择排序
void selectionSort(vector<int>& arr) {
  int len = arr.size();
  for (int i = 0; i < len; ++i) {
    int select_idx = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[j] < arr[select_idx]) {
        select_idx = j;
      }
    }
    if (select_idx != i) {
      swap(arr[i], arr[select_idx]);
    }
  }
}

// 插入排序
void insertionSort(vector<int>& arr) {
  int len = arr.size();
  for (int i = 1; i < len; ++i) {
    int need_insert = arr[i];
    int j = i - 1;
    for (; j >= 0; --j) {
      if (need_insert < arr[j]) {
        arr[j + 1] = arr[j];
      } else {
        break;
      }
    }
    arr[j + 1] = need_insert;
  }
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
  }
  //bubbleSort(arr);
  //insertionSort(arr);
  selectionSort(arr);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
