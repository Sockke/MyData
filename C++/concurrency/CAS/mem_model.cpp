#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// 内存模型:
// 内存模型是硬件层面上的概念, 它表示指令的执行顺序是由编译器和处理器共同决定的
// 因此在不同的平台下, 由于编译器或处理器的优化, 导致指令的执行顺序有所改变
//
// 这也就是说, 对于原子类型的操作, 
// 原子类型操作本身是不可剥夺的, 要么执行完成, 要么不执行,
// 但是原子类型操作彼此之间的执行顺序是不固定的, 
// 当然在x86体系下是一种强顺序, 但是还是要考虑其他平台存在的这种情况
//
// C++提供了std::memory_order一系列的控制原子操作顺序的参数
// 在适当的场景下会有所应用

std::atomic<int> a(0);
std::atomic<int> b(0);

void func() {
  int t = 1;
  a.store(t, std::memory_order_relaxed);
  b.store(2, std::memory_order_relaxed);
}
void show() {
  // 打印可能是 0 2, 因为可能b.store先执行了
  std::cout << a << b << std::endl;
}

int main() {
  std::thread t1(func);
  std::thread t2(show);
  t1.join();
  t2.join();
  return 0;
}
