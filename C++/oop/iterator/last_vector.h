#pragma once
#include <iostream>

template<class T>
struct CAlloctor {
  // 内存开辟
  T* allocate(size_t size) {
    return (T*)malloc(sizeof(T) * size);
  }
  // 内存释放
  void deallocate(T* ptr) {
    free(ptr);
  }
  // 构造对象
  void construct(T* ptr, const T& obj) {
    new (ptr) T(obj);
  }
  // 析构对象
  void destroy(T* obj) {
    obj->~T();
  }
};

template<class T, class Alloc = CAlloctor<T>>
class Vector {
  public:
    Vector(size_t size = 5) 
      : _first(_alloc.allocate(size))
      , _last(_first)
      , _end(_first + size)
    {}
    ~Vector() {
      // 析构对象
      int datesize = _last - _first;
      for (int i = 0; i < datesize; ++i) {
        _alloc.destroy(_first + i);
      }
      // 释放内存
      _alloc.deallocate(_first);
      _first = _last = _end = nullptr;
    }
    Vector(const Vector<T>& vec) {
      int size = vec._last - vec._first;
      // 内存开辟
      _first = _alloc.allocate(size);
      // 构造对象
      int datesize = vec._last - vec._first;
      for (int i = 0; i < datesize; ++i) {
        _alloc.construct(_first + i, vec._first[i]);
      }
      _last = _first + datesize;
      _end = _first + size;
    }
    Vector<T>& operator=(const Vector<T>& vec) {
      if (this == &vec) {
        return *this;
      }
      // 析构对象
      int datesize = vec._last - vec._first;
      for (int i = 0; i < datesize; ++i) {
        _alloc.destroy(_first + i);
      }
      // 释放内存
      _alloc.deallocate(_first);
      // 开辟内存
      int size = vec._end - vec._first;
      _first  = _alloc.allocate(size);
      // 构造对象
      for (int i = 0; i < datesize; ++i) {
        _alloc.construct(_first + i, vec._first[i]);
      }
      _last = _first + datesize;
      _end = _first + size;
      return *this;
    }
    // push_back
    void push_back(const T& t) {
      if (full()) {
        increment();
      }
      // 构造对象
      _alloc.construct(_last++, t);
    }
    void pop_back() {
      if (empty()) {
        return;
      }
      // 析构对象
      _alloc.destroy(--_last);
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
    // []
    int size() const {
      return _last - _first;
    }
    T& operator[](int index) {
      if (index < 0 || index >= size()) {
        throw "out of range exception";
      }
      return _first[index];
    }
    const T& operator[](int index) const {
      return _first[index];
    }

    class Iterator {
      public:
        Iterator(T* p) : _p(p) {}
        // !=
        bool operator!=(const Iterator& it) const {
          return _p != it._p;
        }
        // *
        T& operator*() {
          return *_p;
        }
        const T& operator*() const {
          return *_p;
        }
        // ->
        T* operator->() const {
          return _p;
        }
        // ++
        void operator++() {
          ++_p;
        }
        void operator++(int) {
          Iterator(_p++);
        }
      private:
        T* _p;
    };
    Iterator begin() {
      return Iterator(_first);
    }
    Iterator begin() const {
      return Iterator(_first);
    }
    Iterator end() {
      return Iterator(_last);
    }
    Iterator end() const {
      return Iterator(_last);
    }
  private:
    void increment() {
      int size = _end - _first;
      // 开辟内存
      T* newvec = _alloc.allocate(size * 2);
      // 构造对象
      int datesize = _last - _first;
      for (int i = 0; i < datesize; ++i) {
        _alloc.construct(newvec + i, _first[i]);
      }
      // 析构对象
      for (int i = 0; i < datesize; ++i) {
        _alloc.destroy(_first + i);
      }
      // 释放内存
      _alloc.deallocate(_first);
      _first = newvec;
      _last = _first + datesize;
      _end = _first + size;
    }
  private:
    T* _first;
    T* _last;
    T* _end;
    Alloc _alloc;
};

