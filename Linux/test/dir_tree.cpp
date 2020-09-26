#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <assert.h>
using namespace std;

vector<string> getDirs(string dir) {
  vector<string> arr;
  DIR* d = opendir(dir.c_str());
  if (d == nullptr) {
    return vector<string>();
  }
  struct dirent* entry;
  while ((entry = readdir(d)) != nullptr) {
    string name = entry->d_name;
    if (name != "." && name != "..") {
      arr.push_back(entry->d_name);
    }
  }
  closedir(d);
  return arr;
}

int i = 0;

void printDir(string dir) {
  vector<string> dirs = getDirs(dir);
  for (const auto& e : dirs) {
    ++i;
    int tmp = i;
    while (tmp--) {
      cout << "--";
    }
    cout << e << endl;
    printDir(e);
    --i;
  }
}

int main() {
  printDir(".");
  return 0;
}


