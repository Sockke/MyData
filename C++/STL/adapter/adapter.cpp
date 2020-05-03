#include <iostream>
#include <stack>
#include <queue>

// 容器适配器:
// 1. 适配器底层没有自己的数据结构, 只是另一个容器的封装, 其内部实现的方法依赖于这个容器
// 2. 没有实现迭代器

#if 0
template <class T, class Container = std::deque<T>>
class Stack {
  public:
    void push(const T& data) {
      _con.push_back(data);
    }
    void pop() {
      _con.pop_back();
    }
    T top() const {
      return _con.back();
    }
    bool empty() const {
      return _con.empty();
    }
  private:
    Container _con;
};

int main() {
  Stack<int> s;
  s.push(9);
  s.push(5);
  s.push(2);
  s.push(7);
  while (!s.empty()) {
    std::cout << s.top() << " ";
    s.pop();
  }
  std::cout << std::endl;
  return 0;
}
#endif

#if 0
template <class T, class Container = std::deque<T>>
class Queue {
  public:
    void push(const T& data) {
      _con.push_back(data);
    }
    void pop() {
      _con.pop_front();
    }
    T front() const {
      return _con.front();
    }
    bool empty() const {
      return _con.empty();
    }
  private:
    Container _con;
};

int main() {
  Queue<int> q;
  q.push(9);
  q.push(5);
  q.push(2);
  q.push(7);
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
  return 0;
}
#endif

int main() {
  // 默认是大根堆结构
  std::priority_queue<int> pq;
  pq.push(9);
  pq.push(5);
  pq.push(2);
  pq.push(7);
  while (!pq.empty()) {
    std::cout << pq.top() << " ";
    pq.pop();
  }
  std::cout << std::endl;
  return 0;
}
