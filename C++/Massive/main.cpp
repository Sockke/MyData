#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <functional>
#include <bitset>
#include <algorithm>
using namespace std;

const int LEN = 100;
const int FILE_LEN = 10;
int hash_func(int num) {
  int fenmu = LEN / FILE_LEN;
  int idx = num / fenmu;
  if (idx == FILE_LEN) {
    --idx;
  }
  return idx;
}
int main() {
  FILE* fp = fopen("big.txt", "wb+");
  for (int i = 0; i < LEN; ++i) {
    int num = rand() % LEN;
    fwrite(&num, sizeof(int), 1, fp);
  }
  // 划分小文件, 并将大文件中的数据映射到小文件中
  vector<FILE*> fps(FILE_LEN, nullptr);
  for (int i = 0; i < FILE_LEN; ++i) {
    string fname = "small" + to_string(i);
    fps[i] = fopen(fname.c_str(), "wb+");
  }
  fseek(fp, 0, SEEK_SET);
  while (!feof(fp))  {
    int num = 0;
    int size = fread(&num, sizeof(int), 1, fp);
    if (size > 0) {
      int idx = hash_func(num);
      fwrite(&num, sizeof(int), 1, fps[idx]);
    }
  }
  fseek(fp, 0, SEEK_SET);
  for (int i = 0; i < FILE_LEN; ++i) {
    fseek(fps[i], 0, SEEK_SET);
    vector<int> arr;
    while (!feof(fps[i])) {
      int num = 0;
      int size = fread(&num, sizeof(int), 1, fps[i]);
      if (size > 0) {
        arr.push_back(num);
      }
    }
    sort(arr.begin(), arr.end());
    for (auto& e : arr)  {
      fwrite(&e, sizeof(int), 1, fp);
    }
  }

  fseek(fp, 0, SEEK_SET);
  while (!feof(fp)) {
    int num = 0;
    int size = fread(&num, sizeof(int), 1, fp);
    if (size > 0) {
      cout << num << " ";
    }
  }
  cout << endl;

  return 0;
}

#if 0
// 使用位图来解决查重问题, 可以使用2个位图
const int LEN = 1000;
int main() {
  bitset<LEN> has_bit(0);
  bitset<LEN> is_repeat(0);
  FILE* fp = fopen("big.txt", "wb+");
  for (int i = 0; i < LEN; ++i) {
    int num = rand()%LEN;
    fwrite(&num, sizeof(int), 1, fp);
  }
  fseek(fp, 0, SEEK_SET);
  while (!feof(fp)) {
    int num = 0;
    int size = fread(&num, sizeof(int), 1, fp);
    if (size > 0) {
      if (has_bit[num] == 1) {
        is_repeat.set(num);
      } else {
        has_bit.set(num);
      }
    }
  }
  for (int i = 0; i < LEN; ++i) {
    if (is_repeat[i] == 1) {
      cout << i << " ";
    }
  }
  cout << endl;
  fclose(fp);
  return 0;
}
#endif

#if 0
// 对于unsigned类型的非重复的整数数据的排序, 可以采用位图来实现
// 或者对于unsigned类型的整数数据的查重,去重问题
const int LEN = 1000;
int main() {
  FILE* fp = fopen("big.txt", "wb+");
  for (int i = 0; i < LEN*10; ++i) {
    int num = rand() % LEN;
    fwrite(&num, sizeof(int), 1, fp);
  }
  bitset<LEN> bit;
  fseek(fp, 0, SEEK_SET);
  while (!feof(fp))  {
    int num = 0;
    int size = fread(&num, sizeof(int), 1, fp);
    if (size > 0) {
      bit.set(num);
    }
  }
  for (int i = LEN-1, k = 10; i >= 0 && k > 0; --i, --k) {
    if (bit[i] == 1) {
      cout << i << " ";
    }
  }
  cout << endl;
  fclose(fp);
  return 0;
}
#endif

#if 0
/*
  400M, 每个数据占4字节, 共4G内存的需要, 分成11个文件
  10亿的数据, 求重复次数前10大的, 以整数为例
  1. 分治将大文件平均分成小文件, 通过hash将大文件中的数据映射到小文件中,
  对小文件的数据依次读取到内存中, 放到小根堆中
  2. 如果是unsigned类型的整数, 可以考虑使用位图
*/

const int k = 10;
int main() {
  // 模拟出一个大文件
  FILE* fp = fopen("big.txt", "wb");
  for (int i = 0; i < 100000; ++i) {
    int num = rand() % 10000;
    fwrite(&num, sizeof(int), 1, fp);
  }
  fclose(fp);
  // 分成小文件, 并将数据映射到小文件中
  vector<FILE*> fps(11, nullptr);
  for (int i = 0; i < 11; ++i) {
    string fname = "small" + to_string(i);
    fps[i] = fopen(fname.c_str(), "a+");
  }
  hash<int> hash_func;
  fp = fopen("big.txt", "r");
  while (!feof(fp)) {
    int num = 0;
    int size = fread(&num, sizeof(int), 1, fp);
    if (size > 0) {
      int idx = hash_func(num) % 11;
      fwrite(&num, sizeof(int), 1, fps[idx]);
    }
  }
  // 依次读取每个小文件
  using TYPE = pair<int, int>;
  using FUNC = function<bool(const TYPE&, const TYPE&)>;
  priority_queue<TYPE, vector<TYPE>, FUNC> q([](const TYPE& l, const TYPE& r)->bool{
    return l.second > r.second;
  });
  unordered_map<int, int> m;
  for (int i = 0; i < 11; ++i) {
    m.clear();
    fseek(fps[i], 0, SEEK_SET);
    while (!feof(fps[i])) {
      int num = 0;
      int size = fread(&num, sizeof(int), 1, fps[i]);
      if (size > 0) {
        ++m[num];
      }
    }
    int len = q.size();
    if (len < k) {
      auto it = m.begin();
      for (int i = len; i < k && it != m.end(); ++i, ++it) {
        q.push(*it);
      }
    } else {
      for (auto& e : m) {
        int data = q.top().second;
        if (e.second > data) {
          q.pop();
          q.push(e);
        }
      }
    }
  }
  for (auto& e : fps) {
    fclose(e);
  }
  while (!q.empty()) {
    TYPE data = q.top();
    cout << data.first << ":" << data.second << endl;
    q.pop();
  }
  return 0;
}
#endif
