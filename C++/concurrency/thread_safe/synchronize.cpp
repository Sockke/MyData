#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using std::cout;
using std::endl;

// 存在竞态条件的代码: 临界区代码段
// 多个线程访问具有竞态条件的资源会产生线程安全问题
// 需要保证原子操作, 可以通过互斥锁, CAS原子操作等保证线程安全
//
// 保证线程同步需要通过互斥量, 或者条件变量来实现同步
// C++11提供了condition_variable, 可以通过wait让线程挂起等待, notify_all/notify_one来唤醒线程
// wait使得线程进入等待, 并释放锁资源
// notify_all使得线程从等待进入阻塞状态, 获取锁资源后继续执行

std::mutex mtx;
std::condition_variable con;

class Queue {
  public:
    void myPut(int val) {
      std::unique_lock<std::mutex> ulock(mtx);
      while (!_queue.empty()) {
        // 等待消费者去消费
        con.wait(ulock);
      }
      _queue.push(val);
      cout << "生产了第" << val << "号产品" << endl;
      // 通知消费者去消费
      con.notify_all();
    }
    void myGet() {
      std::unique_lock<std::mutex> ulock(mtx);
      while (_queue.empty()) {
        // 等待生产者去生产
        con.wait(ulock);
      }
      cout << "消费了第" << _queue.front() << "号产品" << endl;
      _queue.pop();
      // 通知生产者去生产
      con.notify_all();
    }
  private:
    std::queue<int> _queue;
};

void consume(Queue& q) {
  for (int i = 0; i < 10; ++i) {
    q.myGet();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void produce(Queue& q) {
  for (int i = 0; i < 10; ++i) {
    q.myPut(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int main() {
  Queue q;
  std::thread consumer(consume, std::ref(q));
  std::thread producer(produce, std::ref(q));
  consumer.join();
  producer.join();
  return 0;
}
