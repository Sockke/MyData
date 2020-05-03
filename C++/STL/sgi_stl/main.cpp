#include <iostream>
#include <vector>

using namespace std;

int main() {
  
  return 0;
}

#if 0
enum {_ALIGN = 8};
size_t _S_round_up(size_t __bytes) {
  return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1));
}
size_t _S_freelist_index(size_t __bytes) {
  return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
}

int main() {
  cout << _S_round_up(4) << endl;
  cout << _S_freelist_index(4) << endl;
  return 0;
}
#endif
