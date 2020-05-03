#include <iostream>
#include <vector>
#include <list>

// 自定义pair对象
template<class K, class V>
struct MyPair {
  MyPair(const K& key = K(), const V& val = V())
    : first(key), second(val) {}
  K first;
  V second;
};

// 拉链法实现hash
template<class K, class V>
class HashBucket {
  public:
    using Pair = MyPair<K, V>; // C++11 == typedef/typename MyPair<K, V> Pair;
    HashBucket(size_t size = 3, double loadfactor = 0.75) 
      : _bucketUsed(0), _loadfactor(loadfactor) {
        _bucket.resize(size, std::list<Pair>());
      }
    void insert(const Pair& p) {
      // 判断是否需要扩容
      if (overload()) {
        increment();
      }
      int index = getIndexByHash(p.first, _bucket.size());
      std::list<Pair>& curlist = _bucket[index];
      if (curlist.empty()) { // 直接插入
        curlist.push_back(p);
        ++_bucketUsed;
        return;
      }  
      // 插入/查重更新
      for (auto& e : curlist) {
        if (e.first == p.first) { // 查重更新后直接返回
          e.second = p.second;
          return;
        }
      }
      curlist.push_back(p); // 插入
    }

    void erase(const K& key) {
      int index = getIndexByHash(key, _bucket.size());
      std::list<Pair>& curlist = _bucket[index];
      if (curlist.empty()) { // 如果链表为空直接返回
        return;
      }  
      // 遍历链表查找并删除
      auto it = curlist.begin();
      while (it != curlist.end()) {
        if (it->first == key) {
          curlist.erase(it);
          if (curlist.empty()) {
            --_bucketUsed;
          }
          return;
        }
        ++it;
      }
    }

    V& operator[](const K& key) {
      int index = getIndexByHash(key, _bucket.size());
      std::list<Pair>& curlist = _bucket[index];
      for (auto& e : curlist) {
        if (e.first == key) { // 如果存在, 直接返回该val的引用
          return e.second;
        }
      }
      curlist.push_front({key, V()}); // 不存在, 插入头部并返回该val的引用
      return curlist.begin()->second;
    }
  private:
    std::vector< std::list<Pair> > _bucket;
    size_t _bucketUsed;
    double _loadfactor;

    // 根据当前负载, 判断是否需要扩容
    bool overload() {
      if (_bucketUsed * 1.0 / _bucket.size() >= _loadfactor) {
        return true;
      }
      return false;
    }
    // 扩容函数
    void increment()  {
      // 保留原来的_bucket, 通过容器中的swap方法将原先的_bucket退化为临时变量保存到oldBucket中
      std::vector< std::list<Pair> > oldBucket;
      oldBucket.swap(_bucket);
      // 初始化资源
      int newsize = 2 * _bucket.size() + 1;
      _bucket.resize(newsize);
      _bucketUsed = 0;
      // 重新映射
      for (size_t i = 0; i < oldBucket.size(); ++i) {
        std::list<Pair>& curlist = oldBucket[i];
        // 把链表的一个或几个结点摘下来, 直接挂到另一个链表中splice
        // list1.splice(list1.begin(), list2, list2.begin())
        // 把list2容器的begin这个位置的结点摘下来, 放到list1中的begin位置
        // list1.splice(list1.begin(), list2, list2.begin(), list2.end())
        // 把list2容器的begin到end这个位置的所有结点摘下来, 放到list1中的begin位置
        auto it = curlist.begin();
        while (it != curlist.end()) {
          int index = getIndexByHash(it->first, newsize);
          if (_bucket[index].empty()) {
            ++_bucketUsed;
          }
          // _bucket[index].push_back({it->first, it->second}); 存在结点的新拷贝, 效率低, 浪费临时空间
          // 将curlist中的it指向的结点摘下来, 挂到_bucket[index]中的end处
          _bucket[index].splice(_bucket[index].end(), curlist, it);
          it = curlist.begin(); // it失效, 更新it, 每次都从头部进行重新映射
        }
      }
    }
    // Hash函数, 除留余数法
    int getIndexByHash(const K& key, size_t size) {
      int index = key % size;
      return index;
    }
};

