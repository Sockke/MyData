#include <iostream>
#include <set>
#include <queue>
#include <string>
using namespace std;


class Student {
  public:
    Student(int id, string name)
      : _id(id)
      , _name(name)
    {}
    // 必须实现二元的函数对象
    friend bool operator<(const Student& left, const Student& right);
    //int getId() const {
    //  return _id;
    //}
  private:
    int _id;
    string _name;
    friend ostream& operator<<(ostream& os, const Student& s);
};
ostream& operator<<(ostream& os, const Student& s) {
  os << s._id << ":" << s._name;
  return os;
}
bool operator<(const Student& left, const Student& right) {
  return left._id < right._id;
}

//struct myCompare {
//  bool operator()(const Student& left, const Student& right) {
//    return left.getId() < right.getId();
//  }
//};

int main() {
  set<Student> s;
  s.insert(Student(6, "张三"));
  s.insert(Student(4, "李四"));
  s.insert(Student(12, "王五"));
  for (const auto& e : s) {
    cout << e << endl;
  }
  return 0;
}

#if 0
int main() {
  //set<int, greater<int>> s;
  //s.insert(9);
  //s.insert(5);
  //s.insert(2);
  //s.insert(7);
  //for (const auto& e : s) {
  //  cout << e << " ";
  //}
  //cout << endl;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < 10; ++i) {
    pq.push(rand() % 100 + 1);
  }
  while (!pq.empty())  {
    cout << pq.top() << " ";
    pq.pop();
  }
  cout << endl;
  return 0;
}
#endif
