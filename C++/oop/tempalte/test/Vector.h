#pragma once
#include <iostream>

template<class T>
class Vector {
  public:
    Vector(const int size = 5) 
      : _first(new T[size])
      , _last(_first)
      , _end(_first + size)
    {}
    ~Vector() {
      delete[] _first;
    }
    Vector(const Vector<T>& vec) {
      int size = vec._end - vec._first;
      _first = new T[size];
      int datelen = vec._last - vec._first;
      for (int i = 0; i < datelen; ++i) {
        _first[i] = vec._first[i];
      }
      _last = _first + datelen;
      _end = _first + size;
    }
    Vector<T>& operator=(const Vector<T>& vec) {
      if (this == &vec) {
        return *this;
      }
      delete[] _first;
      int size = vec._end - vec._first;
      _first = new T[size];
      int datelen = vec._last - vec._first;
      for (int i = 0; i < datelen; ++i) {
        _first[i] = vec._first[i];
      }
      _last = _first + datelen;
      _end = _first + size;
    }
    // 在末尾添加元素
    void push_back(const T& e) {
      if (full()) {
        increment();
      }
      *_last++ = e;
    }
    // 从末尾移除元素
    void pop_back() {
      if (empty()) {
        return;
      }
      --_last;
    }
    // 获取结尾元素
    T back() const {
      return *(_last - 1);
    }
    bool full() const {
      return _last == _end;
    }
    bool empty() const {
      return _last == _first;
    }
  private:
    void increment() {
      int size = _end - _first;
      T* newvec = new T[size * 2];
      int datelen = _last - _first;
      for (int i = 0; i < datelen; ++i) {
        newvec[i] = _first[i];
      }
      delete[] _first;
      _first = newvec;
      _last = _first + datelen;
      _end = _first + size * 2;
    }
  private:
    T* _first; // 向量空间的起始位置
    T* _last; // 最后一个有效元素的后继
    T* _end; // 向量空间结束位置的后继
};

