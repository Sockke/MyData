#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BitSet {
  public:
    BitSet(size_t num) {
      _bitmap.resize(num / 32 + 1, 0);
    }
    void Set(size_t num) {
      size_t index = num / 32;
      size_t bitindex = num % 32;
      _bitmap[index] |= (1 << bitindex);
    }
    bool Find(size_t num) {
      size_t index = num / 32;
      size_t bitindex = num % 32;
      return (_bitmap[index] >> bitindex) & 1;
    }
    void Reset(size_t num) {
      size_t index = num / 32;
      size_t bitindex = num % 32;
      _bitmap[index] &= ~(1 << bitindex);
    }
    //void show() {
    //  for (size_t i = 0; i < _bitmap.size(); ++i) {
    //    for (size_t j = 0; j < 32; ++j) {
    //      cout << ((_bitmap[i] >> j) & 1) << " ";
    //    }
    //    cout << endl;
    //  }
    //}
  private:
    vector<int> _bitmap;
};
