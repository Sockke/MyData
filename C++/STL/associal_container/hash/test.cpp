#include "my_hash.h"
using std::cout;
using std::endl;

int main() {
  HashBucket<int, std::string> myHash;
  myHash.insert({1, "sock"});
  myHash.insert({3, "liuchen"});
  myHash.insert({8, "laoma"});
  myHash.insert({9, "liuwei"});
  myHash.insert({11, "an"});
  cout << myHash[9] << endl;
  cout << myHash[11] << endl;
  myHash.erase(8);
  cout << myHash[8] << endl;
  return 0;
}
