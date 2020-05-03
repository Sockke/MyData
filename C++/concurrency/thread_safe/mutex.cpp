#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>

using std::cout;
using std::endl;

// 保证线程安全, 可以通过互斥锁来实现
// 简单的加解互斥锁会存在资源泄漏引起的死锁问题,
// 比如说在线程解锁之前发生异常或直接返回等.
// 可以通过RAII来管理锁资源, C++11提供了lock_guard和unique_lock
//
// lock_guard类似于智能指针中的scoped_ptr, 删除了拷贝构造和赋值运算符重载
// 不允许锁资源的拷贝和赋值
// unique_lock类似于智能指针中的unique_ptr, 提供了带右值引用参数的拷贝构造和赋值运算符重载
// 允许锁资源以临时变量的形式进行拷贝和赋值
// 
// lock_guard在性能上略优于unique_lock, 一般在不受锁粒度变化的影响的话, 优先使用lock_guard
// unique_lock可以动态的控制锁粒度, 因为它提供了lock与unlock接口, 使用起来更加灵活, 但是
// 正是这些标记带走了一部分性能

int counts = 100;
std::mutex mtx;

void sellTickets(int id) {
  while (counts > 0)  {
    //mtx.lock(); 
    {
      //std::lock_guard<std::mutex> llock(mtx);
      std::unique_lock<std::mutex> ulock(mtx);
      if (counts > 0) {
        cout << "窗口" << id << ":" << counts << endl;;
        --counts;
      }
    }
    //mtx.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int main() {
  std::vector<std::thread> tlist; 
  for (int i = 1; i <= 3; ++i) {
    tlist.push_back(std::thread(sellTickets, i));
  }
  std::for_each(tlist.begin(), tlist.end(), std::mem_fn(&std::thread::join));
  return 0;
}
