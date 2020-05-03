#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <vector>
using std::cout;
using std::endl;

// bind
// 1. 由于C++标准库中的bind1st与bind2nd只能将二元的函数对象转化为一元函数对象,
// 对于相对复杂的函数对象的参数绑定, 就必须要用到bind
// 2. bind是boost库中的绑定器, C++11后将其纳入到C++标准库中
// 3. bind可以完成对复杂函数对象的参数绑定, 
// 通过std::placeholders::_1等占位符来指定待传参数, 并且还可以控制参数传递的顺序
// 4. function可以将bind返回的函数对象保存下来

// 通过bind与function实现线程池
// 任务类
class Task {
  public:
    Task(std::function<void()> func) : _func(func) {}
    std::thread start() { // 通过线程开启任务
      return std::thread(_func);
    }
  private:
    std::function<void()> _func; // 函数对象, 完成指定的任务
};

// 线程池类
class ThreadPool {
  public:
    ThreadPool(int size) {
      // 创建指定的任务对象, 并为其分配任务
      for (int i = 0; i < size; ++i)  {
        // 通过bind将成员函数转化为普通的void()函数对象
        _tasks.push_back(new Task(std::bind(&ThreadPool::runInThread, this, i)));
      }
    }
    ~ThreadPool() {
      for (auto& e : _tasks) {
        delete e;
      }
    }
    // 开启线程池
    void threadStart() {
      for (auto& e : _tasks) { // 让所有的任务对象执行任务, 并保存所有线程
        _threads.push_back(e->start());
      }
      for (auto& e : _threads) { // join线程
        e.join();
      }
    }
  private:
    void runInThread(int id) { // 任务
      cout << "call runInThread id:" << id << endl;
    }
  private:
    std::vector<Task*> _tasks;
    std::vector<std::thread> _threads;
};

void show(const std::string& info) {
  cout << info << endl;
}
int main() {
  //ThreadPool pool(10);
  //pool.threadStart();
  std::bind(show, std::placeholders::_1)("hehe");
  return 0;
}
