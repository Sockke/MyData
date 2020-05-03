#pragma once
#include <iostream>
#include <mutex>

std::mutex mtx;

// 不是线程安全的, 不可重入
// 缓存带来的问题:
// 每个线程会对_singleton进行单独的缓存, 每个线程不是直接对内存中的_singleton进行操作,
// 而是对自己缓存中的_singleton进行操作, 因此在多线程环境下, 依然不是线程安全的.
// 因此要防止对每个线程产生缓存

/*
class Singleton {
  public:
    volatile Singleton* getInstance() {
      // 防止对象已创建, 但每次还要进行加解锁的情况, 提高效率
      if (_singleton == nullptr) {
        mtx.lock();
        if (_singleton == nullptr) {
          // 开辟内存, 构造对象, 给_single赋值
          _singleton = new Singleton();
        }
        mtx.unlock();
      }
      return _singleton;
    }
  private:
    Singleton() {
      std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // volatile 保证内存的可见性, 每个线程对_singleton访问时, 不会对_singleton缓存
    static volatile Singleton* _singleton;
};
volatile Singleton* Singleton::_singleton = nullptr;
*/

class Singleton {
  public:
    static Singleton* getInstance() {
      // 静态的局部变量, 在汇编层面自动进行了加解锁操作, 因此是线程安全的
      static Singleton _singleton;
      return &_singleton;
    }
    ~Singleton() {
      std::cout << "~Singleton()" << std::endl;
    }
  private:
    Singleton() {
      std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
