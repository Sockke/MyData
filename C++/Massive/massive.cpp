#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
using namespace std;

/*
  海量数据求top k问题:
  1. 求top k问题, 可以使用大根堆/小根堆, 或者快排划分的思想
  2. 海量数据, 需要先进行分治, 将大文件中的数据划分到小文件中

  海量数据查重/去重问题:
  1. 位图(unsigned int)
  2. 查重可以使用hash表
  3. 海量数据查重, 需要先进行分治, 将大文件中的数据划分到小文件中
  4. 布隆过滤器, 字典树等
*/

/*
  一个大文件中有10亿个数据, 求前十大的数据, 或者找出重复的数据
*/
/*
  两个文件中都有1亿个整数, 求前十大的整数, 或者找出重复的整数
*/

/*
  一个大文件中有10亿个整数, 求重复次数前十大的整数
  1. 先将大文件划分成小文件
  2. 根据hash映射函数, 读取大文件的数据到指定的小文件中
  3. 依次读取小文件的数据到内存, 进行重复次数的top k问题的求解
*/
int main() {
  FILE* fp = fopen("./data.txt", "wb");
  for (int i = 0; i < 1000000; ++i) {
    int data = rand() % 10000;
    fwrite(&data, 4, 1, fp);
  }
  fclose(fp);

  fp = fopen("./data.txt", "rb");
  // 划分小文件, 10亿整数= 4 * 1G = 4G -> 统计次数的话 2 * 4G = 8G
  // 如果内存限制是400M, 那么最少需要划分 8G/400M = 20个
  // hash函数使用除留余数法, 文件个数尽量是素数, 那么就划分23个
  const int minifile_size = 23;
  vector<FILE*> fps(minifile_size);
  for (int i = 0; i < minifile_size; ++i) {
    char filename[32] = {0};
    sprintf(filename, "data%d.txt", i + 1);
    fps[i] = fopen(filename, "wb+");
  }
  // 将大文件中的整数划分到小文件中
  while (!feof(fp)) {
    int data = 0;
    int size = fread(&data, 4, 1, fp);
    if (size > 0) {
      int index = data % minifile_size;
      fwrite(&data, 4, 1, fps[index]);
    }
  }
  // 读取小文件中的整数到内存进行top k问题的求解
  using P = pair<int, int>;
  using FUNC = function<bool(const P&, const P&)>;
  priority_queue<P, vector<P>, FUNC> q([](const P& l, const P& r)->bool{
    return l.second > r.second;
  });
  for (int i = 0; i < minifile_size; ++i) {
    unordered_map<int, int> m;
    // 刚才将数据划分到小文件的过程中, 文件指针已经到末尾了
    // 需要调整到起始位置
    fseek(fps[i], 0, SEEK_SET);
    while (!feof(fps[i])) {
      int data = 0;
      int size = fread(&data, 4, 1, fps[i]);
      if (size > 0) {
        ++m[data];
      }
    }
    if (q.size() < 10) {
      auto it = m.begin();
      for (size_t i = 0; (i < 10 - q.size()) && (it != m.end()); ++i, ++it) {
        q.push(*it);
      }
    }
    for (auto& kv : m) {
      if (kv.second > 1) {
        P p = q.top();
        if (kv.second > p.second) {
          q.pop();
          q.push(kv);
        }
      }
    }
  }
  for (auto& e : fps) {
    fclose(e);
  }
  fclose(fp);
  // 打印重复次数前10大的整数
  while (!q.empty()) {
    P p = q.top();
    cout << p.first << ":" << p.second << endl;
    q.pop();
  }
  return 0;
}
