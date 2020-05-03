#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
  vector<int> aid;
  aid.reserve(right - left + 1);
  int l = left;
  int r = mid + 1;
  while (l <= mid && r <= right) {
    if (arr[l] <= arr[r]) {
      aid.push_back(arr[l++]);
    } else {
      aid.push_back(arr[r++]);
    }
  }
  while (l <= mid) {
    aid.push_back(arr[l++]);
  }
  while (r <= right) {
    aid.push_back(arr[r++]);
  }
  for (int i = left; i <= right; ++i) {
    arr[i] = aid[i - left];
  }
}

void mergeSort(vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void mergeSort(vector<int>& arr) {
  int len = arr.size();
  mergeSort(arr, 0, len - 1);
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
  }
  mergeSort(arr);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
