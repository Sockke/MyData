#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

// std::atomic_flag
// 这是最简单的一种原子类型, 代表一个bool标志.
// 因此它只有两种状态, 分别是设置(test_and_set)和清除(clear)
// 当一个线程首次进行设置时, atomic_flag在硬件上进行一个标记,
// 使得其他线程也尝试去标记的时候会返回false
// 只有当前线程将标记清除的时候
// 其他线程才能进行标记.
// 这样保证了线程操作的原子性
//
// 使用std::atomic_flag来实现简单的自旋锁.
// 自旋锁的原理: 它是一种基于cpu的忙等待.
// 当前线程进行加锁时, 其他线程尝试加锁时会陷入忙等待, 
// 在当前线程释放锁之前, 会循环尝试去加锁.
// 问题:
// 1. 死锁: 线程在持有锁资源的情况下进行递归
// 2. cpu资源消耗: 频繁获取锁资源不成功, 导致cpu繁忙, 其他线程无法有效利用cpu资源
// 优势:
// 1. 实时性强: 该线程不阻塞, 循环尝试获取锁资源
// 2. 避免中断消耗: 不进行中断, 因此没有内核态与用户态的转换消耗

// 实现简单的自旋锁
class spinlock_mutex {
  public:
    // std::atomic_flag通过ATOMIC_FLAG_INIT进行初始化, 默认也是
    spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}
    void lock() {
      // 循环设置不成功, 进行等待
      while (flag.test_and_set(std::memory_order_acquire));
      // 保证当前线程读操作之前执行
    }
    void unlock() {
      // 清除标记
      flag.clear(std::memory_order_release); 
      // 保证当前线程原子写操作完成之后执行
    }
  private:
    std::atomic_flag flag;
};

spinlock_mutex spin;

void func() {
  spin.lock();
  std::cout << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  spin.unlock();
}

int main() {
  std::thread t1(func);
  std::thread t2(func);
  t1.join();
  t2.join();
  return 0;
}
