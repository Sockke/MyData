/*
   LFU算法: 最近不经常使用, 注重的是访问的次数;
   (LRU是最近最少使用, 注重的是上一次使用的时间)

   一个缓存结构需要实现如下功能。

   set(key, value)：将记录(key, value)插入该结构
   get(key)：返回key对应的value值

   但是缓存结构中最多放K条记录，如果新的第K+1条记录要加入，就需要根据策略删掉一条记录，
   然后才能把新记录加入。这个策略为：在缓存结构的K条记录中，哪一个key从进入缓存结构的时刻开始，
   被调用set或者get的次数最少，就删掉这个key的记录；
   如果调用次数最少的key有多个，上次调用发生最早的key被删除
   这就是LFU缓存替换算法。实现这个结构，K作为参数给出
   [要求]
   set和get方法的时间复杂度为O(1)
   */

#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LFU {
  public:
    LFU(int cap)
      : _cap(cap)
      , _mcnt(0)
  {}
    void set(int key, int value) {
      if (_cap <= 0) {return;}
      if (_m.find(key) != _m.end()) {
        _m[key].first = value;
        return;

      }
      if ((int)_m.size() >= _cap) {
        _m.erase(_mlist[_mcnt].front());
        _mit.erase(_mlist[_mcnt].front());
        _mlist[_mcnt].pop_front();

      }
      _m[key] = {value, 1};
      _mcnt = 1;
      _mlist[_mcnt].push_back(key);
      _mit[key] = --_mlist[_mcnt].end();

    }
    int get(int key) {
      if (_m.find(key) == _m.end()) {
        return -1;

      }
      _mlist[_m[key].second].erase(_mit[key]);
      _mlist[++_m[key].second].push_back(key);
      _mit[key] = --_mlist[_m[key].second].end();

      while (_mlist[_mcnt].empty()) {++_mcnt;}

      return _m[key].first;

    }
  private:
    unordered_map<int, pair<int, int>> _m; // 存{key, {value, cnt}}
unordered_map<int, list<int>> _mlist; // 存{cnt, key}
unordered_map<int, list<int>::iterator> _mit; // 存{key, it}

int _cap; // LFU缓存容量
int _mcnt; // 当前数据中最少的访问次数

};

int main() {
  int n = 0, cap = 0;
  while (cin >> n >> cap) {
    LFU lfu(cap);
    for (int i = 0; i < n; ++i) {
      int op = 0;
      cin >> op;
      if (op == 1) {
        int key = 0, value = 0;
        cin >> key >> value;
        lfu.set(key, value);

      } else {
        int key = 0;
        cin >> key;
        int value = lfu.get(key);
        cout << value << endl;
      }
    }
  }
  return 0;
}

