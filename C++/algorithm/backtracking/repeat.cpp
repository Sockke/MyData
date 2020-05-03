#include <iostream>
#include <vector>
using namespace std;

/*
  子集树与排列树的去重
  子集树去重: 子集的概念, 确定性, 因此不能有重复的数字
  将数组进行从小到大排序, 如果当前元素与前一个元素相同了,
  说明已经选择过了, 就不选了

  排列树去重: 相同数字互换位置只能表示1种情况
  对数组从小到大排序, 如果当前需要交换的元素不是本身, 
  并且与需要交换的元素一样, 那就不用交换了
*/

vector<int> arr{1, 1, 2, 2};
const int size = arr.size();

void arrange(int i) {
  if (i == size) {
    for (auto& e : arr) {
      cout << e << " ";
    }
    cout << endl;
  } else {
    for (int k = i; k < size; ++k) {
      // 去重
      if (i != k && arr[k] == arr[k-1]) {
        continue;
      }
      swap(arr[k], arr[i]);
      arrange(i + 1);
      swap(arr[k], arr[i]);
    }
  }
}

vector<int> aid;
void subset(int i) {
  if (i == size) {
    for (auto& e : aid) {
      cout << e << " ";
    }
    cout << endl;
  } else {
    // 去重
    if (i == 0 || arr[i] != arr[i-1]) {
      aid.push_back(arr[i]);
      subset(i + 1);
      aid.pop_back();
    }
    subset(i + 1);
  }
}

int main() {
  //arrange(0);
  subset(0);
  return 0;
}
