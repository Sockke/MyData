#include <iostream>
#include <vector>
using namespace std;

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
    quickSort(arr, left, mid - 1);
    quickSort(arr, mid + 1, right);
  }
}

void quickSort(vector<int>& arr) {
  int len = arr.size();
  quickSort(arr, 0, len - 1);
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
  }
  quickSort(arr);
  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
