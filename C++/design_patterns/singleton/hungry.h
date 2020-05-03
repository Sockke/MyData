#pragma once
#include <iostream>

class Singleton {
  public:
    static Singleton* getInstance() {
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
    static Singleton _singleton;
};
Singleton Singleton::_singleton;

