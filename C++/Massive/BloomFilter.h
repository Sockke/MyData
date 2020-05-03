#pragma once
#include "BitSet.h"

struct HFunc1 {
  size_t operator()(const string& str) {
    size_t _hash = 0;
    for (const auto& e : str) {
      _hash = _hash * 131 + e;
    }
    return _hash;
  }
};

struct HFunc2 {
  size_t operator()(const string& str) {
    size_t _hash = 0;
    for (const auto& e : str) {
      _hash = _hash * 65599 + e;
    }
    return _hash;
  }
};

struct HFunc3 {
  size_t operator()(const string& str) {
    size_t _hash = 0;
    size_t magic = 63689;
    for (const auto& e : str) {
      _hash = _hash * magic + e;
      magic *= 378551;
    }
    return _hash;
  }
};

template <class T, class HFunc1 = HFunc1, class HFunc2 = HFunc2, class HFunc3 = HFunc3>
class BloomFilter {
  public:
    // k * n / ln2 = 1.4 * k -> 计算出一个最大值, 来确定_bitmap的大小
    BloomFilter(size_t n)
      : _bitmap(5 * n), _bitcount(5 * n) {}
    // 置1
    void Set(const T& data) {
      int index1 = HFunc1()(data) % _bitcount;
      int index2 = HFunc2()(data) % _bitcount;
      int index3 = HFunc3()(data) % _bitcount;

      _bitmap.Set(index1);
      _bitmap.Set(index2);
      _bitmap.Set(index3);

      //cout << index1 << " " << index2 << " " << index3 << endl;
    }
    // 查找
    bool Find(const T& data) {
      int index1 = HFunc1()(data) % _bitcount;
      if (!_bitmap.Find(index1)) {
        return false;
      }
      int index2 = HFunc2()(data) % _bitcount;
      if (!_bitmap.Find(index2)) {
        return false;
      }
      int index3 = HFunc3()(data) % _bitcount;
      if (!_bitmap.Find(index3)) {
        return false;
      }
      return true;
    }

    //void show() {
    //  _bitmap.show();
    //}
  private:
    BitSet _bitmap;
    size_t _bitcount;
};
