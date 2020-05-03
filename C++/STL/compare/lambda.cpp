#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>
#include <memory>
#include <fstream>
using std::cout;
using std::endl;

// lambda表达式, 解决预定义函数对象的缺点.
// 预定义函数对象的缺点: 
// 1. 必须要定义一个类, 操作复杂
// 2. 一个类完成一个功能, 灵活性差  
// 3. 该类在进程结束之前一直存在
// lambda表达式的优点:
// 1. 不需要定义类, lambda表达式充当函数对象, 操作简单
// 2. lambda表达式可以灵活的控制函数对象的种类
// 3. lambda表达式只在当前语句中有效, 但是可以通过function来保留, 轻量
//
// [外部变量捕获](参数列表)->返回类型{表达式}
//
// []: 不捕获外部变量
// [a, &b]: 按值捕获a, 按引用捕获b
// [=]: 按值捕获外部所有变量
// [&]: 按引用捕获外部所有变量
// [this]: 捕获外部的this指针

int main() {
  // 智能指针自定义删除器
  std::unique_ptr<FILE, std::function<void(FILE*)>> f_uptr(fopen("lambda.cpp", "r"),
      [](FILE* fp)->void{fclose(fp);cout << "closed" << endl;});
  cout << "dosomething" << endl;
  return 0;
}

#if 0
class Student {
  public:
    Student(int id, double grade) : _id(id), _grade(grade) {}
    double getGrade() const {
      return _grade;
    }
  private:
    int _id;
    double _grade;
};

int main() {
  // 优先级队列, lambda表达式自定义比较规则
  using CFUNC = std::function<bool(const Student&, const Student&)>;
  // 优先级队列的构造函数可以接收一个函数对象
  std::priority_queue<Student, std::vector<Student>, CFUNC> 
    pqueue([](const Student& left, const Student& right)->bool{
      return left.getGrade() > right.getGrade();
    });
  pqueue.push(Student(1, 80));
  pqueue.push(Student(1, 85));
  pqueue.push(Student(1, 78));
  pqueue.push(Student(1, 90));
  while (!pqueue.empty()) {
    cout << pqueue.top().getGrade() << " ";
    pqueue.pop();
  }
  cout << endl;
  return 0;
}
#endif

#if 0
template <class T = int>
struct Swap {
  void operator()(T& a, T& b) {
    int tmp = a;
    a = b;
    b = tmp;
  }
};

int main() {
  // 用lambda表达式写一个交换函数对象
  int a = 10, b = 20;
  //std::function<void()> func = [&a, &b]() ->void{
  //  int tmp = a;
  //  a = b;
  //  b = tmp;
  //};
  // 预定义函数对象
  std::function<void(int&, int&)> func = Swap<>();
  func(a, b);
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  return 0;
}
#endif

#if 0
template <class Container>
void showContainer(Container& con) {
  typename Container::iterator it = con.begin();
  while (it != con.end()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
}

int main() {
  std::vector<int> vec;
  for (int i = 0; i < 10; ++i) {
    vec.push_back(rand() % 100 + 1);
  }
  showContainer(vec);
  std::sort(vec.begin(), vec.end(), std::greater<int>());
  showContainer(vec);
  auto pos = std::find_if(vec.begin(), vec.end(), [](int val)->bool{return val < 70;});
  if (pos != vec.end()) {
    vec.insert(pos, 70);
  }
  showContainer(vec);
  return 0;
}
#endif
