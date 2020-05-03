#include <iostream>
#include <functional>
#include <string>
using namespace std;

// function的实现原理:
// 1. function是类模板的偏特化版本, 将模板参数偏特化为<R(A...)>函数类型
// 2. 构造函数接收指定函数类型
// 3. 提供operator()方法, 使function具备函数对象的功能

template <class T>
class MyFunction {};
// 类模板的偏特化
template <class R, class... A> // 模板提供了模板参数不定参的定义: class...或typename...
class MyFunction<R(A...)> { // 不定参类型: A...
  public:
    using PFUNC = R(*)(A...);
    MyFunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(A... arg) {
      return _pfunc(arg...); // 不定参变量的传递也要以不定参的形式传递: arg...
    }
  private:
    PFUNC _pfunc;
};
void show(string info) {
  cout << info << endl;
}
int sum(int left, int right) {
  return left + right;
}

int main() {
  MyFunction<void(string)> func1 = show;
  func1("sock");
  MyFunction<int(int, int)> func2 = sum;
  cout << func2(10, 20) << endl;
  return 0;
}
