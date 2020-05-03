#include <iostream>
#include <vector>
using namespace std;

// 冒泡排序
void bubbleSort(vector<int>& arr) {
  int len = arr.size();
  for (int i = len-1; i > 0; --i) {
    bool issorted = true;
    for (int j = 0; j < i; ++j) {
      if (arr[j] > arr[j+1]) {
        swap(arr[j], arr[j+1]);
        issorted = false;
      }
    }
    if (issorted) {break;}
  }
}

// 选择排序
void selectSort(vector<int>& arr) {
  int len = arr.size();
  for (int i = 0; i < len-1; ++i) {
    int select_idx = i;
    for (int j = i+1; j < len; ++j) {
      if (arr[select_idx] > arr[j])  {
        select_idx = j;
      }
    }
    if (select_idx != i) {
      swap(arr[i], arr[select_idx]);
    }
  }
}

// 插入排序
void insertSort(vector<int>& arr) {
  int len = arr.size();
  for (int i = 1; i < len; ++i) {
    int insert_num = arr[i];
    int j = i-1;
    for (; j >= 0; --j) {
      if (arr[j] > insert_num) {
        arr[j+1] = arr[j];
      } else {
        break;
      }
    }
    arr[j+1] = insert_num;
  }
}

int partition(vector<int>& arr, int left, int right) {
  int num = arr[left];
  while (left < right) {
    while (left < right && arr[right] > num) {
      --right;
    }
    if (left < right) {
      arr[left] = arr[right];
      ++left;
    }
    while (left < right && arr[left] <= num) {
      ++left;
    }
    if (left < right) {
      arr[right] = arr[left];
      --right;
    }
  }
  arr[left] = num;
  return left;
}
void quickSort(vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = partition(arr, left, right);
    quickSort(arr, left, mid-1);
    quickSort(arr, mid+1, right);
  }
}
void quickSort(vector<int>& arr) {
  quickSort(arr, 0, arr.size()-1);
}


void merge(vector<int>& arr, int left, int mid, int right) {
  vector<int> tmp;
  tmp.reserve(right-left+1);
  int l = left;
  int r = mid + 1;
  while (l <= mid && r <= right) {
    if (arr[l] <= arr[r]) {
      tmp.push_back(arr[l]);
      ++l;
    } else {
      tmp.push_back(arr[r]);
      ++r;
    }
  }
  while (l <= mid) {
    tmp.push_back(arr[l]);
    ++l;
  }
  while (r <= right) {
    tmp.push_back(arr[r]);
    ++r;
  }
  for (int k = left; k <= right; ++k) {
    arr[k] = tmp[k-left];
  }
}
void mergeSort(vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = left + (right-left)/2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);
    merge(arr, left, mid, right);
  }
}
void mergeSort(vector<int>& arr) {
  mergeSort(arr, 0, arr.size()-1);
}

void build(vector<int>& arr, int len, int parent) {
  int max_idx = parent;
  int lchild = parent * 2 + 1;
  int rchild = parent * 2 + 2;
  if (lchild < len && arr[lchild] > arr[max_idx]) {
    max_idx = lchild;
  }
  if (rchild < len && arr[rchild] > arr[max_idx]) {
    max_idx = rchild;
  }
  if (max_idx != parent) {
    swap(arr[max_idx], arr[parent]);
    build(arr, len, max_idx);
  }
}
void heapSort(vector<int>& arr) {
  int len = arr.size();
  for (int i = len/2; i >= 0; --i) {
    build(arr, len, i);
  }
  for (int i = len-1; i > 0; --i) {
    swap(arr[i], arr[0]);
    build(arr, i, 0);
  }
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 10; ++i) {
    arr.push_back(rand() % 100);
  }
  heapSort(arr);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
