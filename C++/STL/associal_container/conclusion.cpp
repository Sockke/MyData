#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>

// 关联式容器:
// 有序关联式容器: set map/multiset multimap
// set: 有序集合, 只存key
// map: 有序映射表, 存key-value
// multiset/multimap: 允许键重复
//
// 无序关联式容器: unordered_set unordered_map/unordered_multiset unordered_multimap
// unordered_set: 无序集合
// unordered_map: 无序映射表
// unordered_multiset/unordered_multimap: 允许键重复
//
// 使用场景:
// 1. 如果考虑数据的顺序, 并且有大量的查询操作, 可以考虑set/map
// 2. 如果不考虑数据的顺序, 并且有大量的查询操作, 可以考虑unordered_set/unordered_map
// 无序关联式容器一般用于海量数据查询, 去重等操作

#if 0
int main() {
  const int SIZE = 100;
  int arr[SIZE] = {0};
  for (int i = 0; i < SIZE; ++i) {
    arr[i] = rand() % 20 + 1;
  }
  // 统计次数
  std::unordered_map<int, int> umap;
  for (const int& e : arr) {
    ++umap[e];
  }
  for (const std::pair<int, int>& e : umap) {
    std::cout << e.first << "=" << e.second << std::endl;
  }
#if 0
  // 查重
  std::unordered_set<int> uset;
  for (const int& e : arr) {
    uset.insert(e);
  }
  for (const int& e : uset) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
#endif
  return 0;
}
#endif

class Student {
  public:
    Student(int id = int(), std::string name = std::string())
      : _id(id)
      , _name(name)
    {}
    bool operator<(const Student& s) const {
      return _id < s._id;
    }
  private:
    int _id;
    std::string _name;
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
std::ostream& operator<<(std::ostream& os, const Student& s) {
  os << s._id << ":" << s._name;
  return os;
}

int main() {
  std::map<int, Student> m;
  m.insert({1, Student(1, "李四")});
  m.insert({3, Student(3, "张三")});
  m.insert({2, Student(2, "王五")});
  auto mit = m.begin();
  while (mit != m.end()) {
    std::cout << mit->second << std::endl;
    ++mit;
  }
  return 0;
}

#if 0
int main() {
  std::set<Student> s;
  s.insert(Student(1, "张三"));
  s.insert(Student(3, "李四"));
  s.insert(Student(2, "王五"));
  std::set<Student>::iterator sit = s.begin();
  while (sit != s.end()) {
    std::cout << *sit << std::endl;
    ++sit;
  }
  return 0;
}
#endif
