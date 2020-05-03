#pragma once
#include <iostream>

template<class T>
struct CAllocator{
  // 内存分配
  T* allocate(size_t size) {
    return (T*)malloc(sizeof(T) * size);
  }
  // 内存释放
  void deallocate(T* ptr) {
    free(ptr);
  }
  // 调用构造函数
  void construct(T* ptr, const T& obj) {
    new (ptr) T(obj);
  }
  // 调用析构函数
  void destroy(T* ptr) {
    ptr->~T();
  }
};

template<class T, class Alloc = CAllocator<T>>
class Vector {
  public:
    Vector(size_t size = 5) 
      : _first(_alloc.allocate(size)) // 开辟内存
      , _last(_first)
      , _end(_first + size)
    {}
    ~Vector() {
      // 调用析构函数
      int datelen = _last - _first;
      for (int i = 0; i < datelen; ++i) {
        _alloc.destroy(_first + i);
      }
      // 释放内存
      _alloc.deallocate(_first);
      _first = _last = _end = nullptr;
    }
    Vector(const Vector<T>& vec) {
      int size = vec._end - vec._frist;
      // 开辟内存
      _first = _alloc.allocate(size);
      // 构造对象
      int datelen = vec._last - vec._first;
      for (int i = 0; i < datelen; ++i) {
        _alloc.construct(_first + i, vec._first[i]);
      }
      _last = _first + datelen;
      _end = _first + size;
    }
    Vector<T>& operator=(const Vector<T>& vec) {
      if (this == &vec) {
        return *this;
      }
      // 调用析构函数
      int datelen = _last - _first;
      for (int i = 0; i < datelen; ++i) {
        _alloc.destroy(_first + i);
      }
      // 释放内存
      _alloc.deallocate(_first);

      // 开辟内存
      int size = vec._end - vec._first;
      _first = _alloc.allocate(size);
      // 构造对象
      datelen = vec._last - vec._first;
      for (int i = 0; i < datelen; ++i) {
        _alloc.construct(_first + i, vec._first[i]);
      }

      _last = _first + datelen;
      _end = _first + size;
      return *this;
    }
    void push_back(const T& e) {
      if (full()) {
        increment();
      }
      // 构造对象
      _alloc.construct(_last, e);
      ++_last;
    }
    void pop_back() {
      if (empty()) {
        return;
      }
      // 析构对象
      --_last;
      _alloc.destroy(_last);
    }
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
      // 开辟新内存
      int size = _end - _first;
      T* newvec = _alloc.allocate(2 * size);
      // 构造对象
      int datelen = _last - _first;
      for (int i = 0; i < datelen; ++i) {
        _alloc.construct(newvec + i, _first[i]);
        _alloc.destroy(_first + i); // 析构对象
      }
      // 释放内存
      _alloc.deallocate(_first);
      _first = newvec;
      _last = _first + datelen;
      _end = _first + 2 * size;
    }
  private:
    T* _first;
    T* _last;
    T* _end;
    Alloc _alloc;
};
