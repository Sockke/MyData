#include <iostream>
using namespace std;

// 默认拷贝构造和赋值的原理?
// 默认是内存拷贝, 即浅拷贝
//
// 什么时候使用自定义的深拷贝?
// 当对象的成员变量中含有指针, 并且该指针指向堆上的一块资源时, 需要进行深拷贝.
// 因为如果让指针进行浅拷贝, 那么俩个指针指向同一块资源, 在进行对象
//
// 拷贝构造与赋值中深拷贝的原理?
// 拷贝构造: 对需要拷贝的堆资源重新开辟一段空间, 然后将对应的资源一一拷贝过去
// 赋值重载: 先将自己的堆资源释放掉, 然后为需要拷贝的堆资源重新开辟一段空间, 
// 将对应的资源一一拷贝过去
//

// 实现一个顺序栈
class SeqStack {
  public:
    SeqStack(int size = 5)
      : _top(-1), _size(size) {
        _seqStack = new int[size];
      }
    ~SeqStack() {
      delete[] _seqStack;
    }
    // 拷贝构造
    SeqStack(const SeqStack& s) {
      int* newStack = new int[s._size];
      for (int i = 0; i <= s._top; ++i) {
        newStack[i] = s._seqStack[i];
      }
      _seqStack = newStack;
      _top = s._top;
      _size = s._size;
    }
    // 拷贝赋值
    SeqStack& operator=(const SeqStack& s) {
      if (this == &s) {
        return *this;
      }
      delete[] _seqStack;
      int* newStack = new int[s._size];
      for (int i = 0; i <= s._top; ++i) {
        newStack[i] = s._seqStack[i];
      }
      _seqStack = newStack;
      _top = s._top;
      _size = s._size;
      return *this;
    }
    void push(int e) {
      if (full()) {
        increment();
      }
      _seqStack[++_top] = e;
      ++_size;
    }
    void pop() {
      if (empty()) {
        return;
      }
      --_top;
      --_size;
    }
    int top() {
      return _seqStack[_top];
    }
    bool full() {
      return _top == _size - 1;
    } 
    bool empty() {
      return _top == -1;
    }
  private:
    void increment() {
      int newsize = _size * 2;
      int* newStack = new int[newsize];
      for (int i = 0; i < _size; ++i) {
        newStack[i] = _seqStack[i];
      }
      delete[] _seqStack;
      _seqStack = newStack;
    }
  private:
    int* _seqStack; 
    int _top;
    int _size;
};

void show(SeqStack& s) {
  while (!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
}
#if 0
int main() {
  SeqStack s;
  s.push(9);
  s.push(5);
  s.push(2);
  s.push(7);
  SeqStack s1(s);
  show(s1);
  SeqStack s2;
  s2 = s;
  show(s2);
  return 0;
}
#endif

// 拷贝构造形参可以按值接收对象吗?
// 不可以, 造成循环调用拷贝构造的情况, 编译时期就不通过
// 赋值运算符重载可以按值接收对象吗?
// 可以, 但是多一次拷贝构造, 效率较低
// 拷贝构造函数使用过程中会产生临时对象吗?
// 会, t = getT();
// 赋值运算符重载在使用过程中会产生临时对象吗?
// 会, t = 10;

class T {
  public:
    T(int ma) : a(ma){
      cout << "T()" << endl;
    }
    T(const T& t) {
      cout << "T(const T&)" << endl;
      a = t.a;
    }
    T& operator=(const T& t) {
      cout << "T& operator=(const T&)" << endl;
      if (this == &t) {
        return *this;
      }
      a = t.a;
      return *this;
    }
  private:
    int a;
};

T getT() {
  T t(1);
  return t;
}

int main() {
  // 在vs下, getT先调用构造函数生成临时变量, 然后再拷贝构造
  // 在gcc下, getT直接返回1来调用构造函数, 编译器进行了优化
  //T t = getT();
  T t(1);
  t = 10; // 先用10调用构造函数生成t对象, 然后再调用赋值重载
  return 0;
}
