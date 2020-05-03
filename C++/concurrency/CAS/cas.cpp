#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
using namespace std;

// CAS的原理:
// 在硬件层面上保证操作的原子性, 在软件层面上认为是无锁操作
// 1. CAS通过3个操作数来保证操作的原子性. 
// 这3个操作数分别为数据内存地址, 期待值, 新值
// 期待值是操作之前获取的值, 新值是预期操作之后的值
// 2. 在进行CAS操作时, 先将内存中的数据与期待值进行比较, 
// 如果相等, 那么将预期的新值写入内存
// 如果不相等, 重新获取内存的值作为预期值, 继续进行比较
// 3. 这样就保证了线程对数据的操作是原子性的


// volatile 防止线程对共享数据进行缓存
volatile atomic_bool ret(false);
volatile atomic_int val(0);

void task() {
  while (!ret) {
    // 让出时间片
    std::this_thread::yield();      
  }
  for (int i = 0; i < 100; ++i) {
    ++val;
  }
}

int main() {
  vector<thread> vthreads;
  for (int i = 0; i < 10; ++i) {
    vthreads.push_back(thread(task));
  }
  std::this_thread::sleep_for(std::chrono::seconds(3));
  ret = true;
  for (int i = 0; i < 10; ++i) {
    vthreads[i].join();
  }
  cout << "val:" << val << endl;
  return 0;
}

#if 0
atomic<int> a(0);
void add() {
  for (int i = 0; i < 1000000; ++i) {
    a++;
  }
}
int main() {
  thread t1(add);
  thread t2(add);
  thread t3(add);
  t1.join();
  t2.join();
  t3.join();
  cout << a << endl;
  cout << atomic_is_lock_free(&a) << endl;
  return 0;
}
#endif
