#include <iostream>
#include <vector>
using namespace std;

/*
  归并排序, 最能体现分治策略的排序算法
  归并排序就是基于分治思想, 将待排数组的规模先划分成子规模,
  当子规模为1时, 那么该规模的数组肯定是有序的.
  最后将所有的子规模进行合并, 最终合并成的原数组是有序的.
*/

#if 0
void merge(vector<int>& arr, int left, int mid, int right) {
  vector<int> tmp;
  tmp.reserve(right - left + 1);
  // 左右规模的数组中, 从左向右谁小谁先放
  // 左规模:[left, mid] 右规模:[mid+1, right]
  int l = left;
  int r = mid + 1;
  while (l <= mid && r <= right) {
    if (arr[l] <= arr[r]) {
      tmp.push_back(arr[l++]);
    } else {
      tmp.push_back(arr[r++]);
    }
  }
  while (l <= mid) {
    tmp.push_back(arr[l++]);
  }
  while (r <= right) {
    tmp.push_back(arr[r++]);
  }
  // 将临时数组中的有序数列写回原数组
  for (int i = left; i <= right; ++i) {
    arr[i] = tmp[i - left];
  }
}

void divide(vector<int>& arr, int left, int right) {
  // 规模变成1了, 肯定是有序的, 不用再划分了
  if (left >= right) {
    return;
  }
  int mid = left + (right - left) / 2;
  // 划分字规模
  divide(arr, left, mid);
  divide(arr, mid + 1, right);
  // 回溯时, 进行子规模的合并
  merge(arr, left, mid, right);
}

void mergeSort(vector<int>& arr) {
  divide(arr, 0, arr.size() - 1);
}

int main() {
  vector<int> arr;
  for (int i = 0; i < 20; ++i) {
    arr.push_back(rand() % 100);
    cout << arr[i] << " ";
  }
  cout << endl;

  mergeSort(arr);

  for (auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
#endif

/*
  合并K个有序的链表
  通过归并排序的思想, 先分治将有序链表的数组规模划分成子规模,
  当规模为1时, 只有一个有序链表, 肯定是有序的,
  然后将子规模的链表进行合并, 最终合并成一个有序链表
*/

struct ListNode {
  ListNode(int data = int())
    : _data(data)
    , _next(nullptr)
  {}
  int _data;
  ListNode* _next;
};

ListNode* listInit(initializer_list<int> l) {
  ListNode* head = new ListNode();
  ListNode* cur = head;
  for (auto& e : l) {
    ListNode* node = new ListNode(e);
    cur->_next = node;
    cur = node;
  }
  return head;
}

ListNode* merge(ListNode* l, ListNode* r) {
  // 把右边的链表插入到左边链表中, 使其有序
  ListNode* cur_l = l;
  ListNode* cur_r = r;
  while (cur_l->_next != nullptr && cur_r->_next != nullptr) {
    if (cur_l->_next->_data <= cur_r->_next->_data) {
      cur_l = cur_l->_next; 
    } else {
      ListNode* cur = cur_r->_next;
      cur_r->_next = cur->_next;
      cur->_next = cur_l->_next;
      cur_l->_next = cur;
      cur_l = cur;
    }
  }
  // 右边链表还每遍历完, 直接连接在后边就行了
  if (cur_l->_next == nullptr) {
    cur_l->_next = cur_r->_next;
  } 
  return l;
}

ListNode* divide(vector<ListNode*>& arr, int left, int right) {
  if (left >= right) {
    return arr[left];
  }
  int mid = left + (right - left) / 2;
  // 划分子规模
  ListNode* l = divide(arr, left, mid);
  ListNode* r = divide(arr, mid + 1, right);
  return merge(l, r); // 合并
}

ListNode* mergeLinks(vector<ListNode*>& arr) {
  return divide(arr, 0, arr.size() - 1);
}

void show(ListNode* head) {
  ListNode* cur = head->_next;
  while (cur != nullptr) {
    cout << cur->_data << " ";
    cur = cur->_next;
  }
  cout << endl;
}

int main() {
  ListNode* head1 = listInit({1, 3, 6, 12});
  ListNode* head2 = listInit({1, 2, 5, 8, 9, 15});
  ListNode* head3 = listInit({4, 11, 19});
  vector<ListNode*> arr;
  arr.push_back(head1);
  arr.push_back(head2);
  arr.push_back(head3);

  ListNode* head = mergeLinks(arr);
  show(head);
  return 0;
}
