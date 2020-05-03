#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// std::atomic<int> ...
// 基本的原子类型, std::atomic<int> ...
// 不支持所谓的拷贝构造和赋值重载函数, 因为涉及到两个对象的数据传递,
// 其组合不可能是原子性的, 因此是被禁止的
// 但是atomic本身提供了operator=, 他返回的不是对象的引用, 而是这个模板类型
//
// 对于原子操作, 一般是通过使用
// a.store(10)进行赋值, 这类似于a = 10
// int b = a.load()进行读取, 这类似于int b = 10
// a.exchange完成了上述两种操作, 先赋值, 然后返回旧值

std::atomic<int> a(0);
std::atomic<int> b(10);
int main() {
  //int b = a.exchange(10); // 类似于a.store(10)并返回旧值
  //std::cout << b << std::endl;
  //std::cout << a << std::endl;
  //int b = 1;
  //bool ret = a.compare_exchange_strong(b, 10);
  //std::cout << ret << std::endl;
  //std::cout << a << std::endl;
  return 0;
}
