#include <iostream>
#include <bitset>
using namespace std;

const int LEN = 1000000;
class BitSet {
  public:
    BitSet() {}
    void insert(size_t i) {
      if (i < LEN) {
        _bset.set(i);
      }
    }
    void erase(size_t i) {
      if (i < LEN) {
        _bset.reset(i);
      }
    }
    bool find(size_t i) {
      if (_bset[i] & 1) {
        return true;
      }
      return false;
    }
    int size() const {
      return _bset.size();
    }
    void show() const {
      for (int i = 0; i < size(); ++i) {
        if (_bset[i] & 1) {
          cout << i << " ";
        }
      }
      cout << endl;
    }
  private:
    bitset<LEN> _bset;
};

int main() {
  BitSet bs;
  bs.insert(9);
  bs.insert(500);
  bs.insert(60000);
  bs.show();
  return 0;
}
