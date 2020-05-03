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
  void destroy(T* ptr) {
    ptr->~T();
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
      verify(_last - 1, _last);
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
    bool operator!=(const Vector<T>& vec) {
      return this != vec;
    }

    // 迭代器, 为了判定迭代器是否失效, 需要迭代器所迭代的容器对象的指针
    class Iterator {
      public:
        friend class Vector<T, Alloc>;   // 一个类的友元类可以访问该类的私有成员
        Iterator(Vector<T>* vec = nullptr, T* p = nullptr)
          : _p(p) 
          , _vec(vec)
        {
          // 将该迭代器对象头插到有效迭代器管理链表中
          Iterator_base* itNode = new Iterator_base(this, _vec->_head._next);
          _vec->_head._next = itNode;
        }
        // !=
        bool operator!=(const Iterator& it) const {
          // 判断迭代器是否失效
          if (_vec == nullptr || _vec != it._vec) {
            throw "iterator incompatable!";
          }
          return _p != it._p;
        }
        // *
        T& operator*() {
          // 判断迭代器是否失效
          if (_vec == nullptr) {
            throw "iterator incompatable!";
          }
          return *_p;
        }
        const T& operator*() const {
          // 判断迭代器是否失效
          if (_vec == nullptr) {
            throw "iterator incompatable!";
          }
          return *_p;
        }
        // ->
        T* operator->() const {
          // 判断迭代器失效
          if (_vec == nullptr) {
            throw "iterator incompatable!";
          }
          return _p;
        }
        // ++
        void operator++() {
          // 判断迭代器失效
          if (_vec == nullptr) {
            throw "iterator incompatable!";
          }
          ++_p;
        }
        void operator++(int) {
          if (_vec == nullptr) {
            throw "iterator incompatable!";
          }
          Iterator(_vec, _p++);
        }
      private:
        T* _p;
        Vector<T, Alloc>* _vec;
    };
    Iterator begin() {
      return Iterator(this, _first);
    }
    Iterator begin() const {
      return Iterator(this, _first);
    }
    Iterator end() {
      return Iterator(this, _last);
    }
    Iterator end() const {
      return Iterator(this, _last);
    }

    Iterator Insert(Iterator it, const T& val) {
      // 不考虑扩容, 不考虑it迭代器中指针的合法性
      // 先构造函数后析构函数
      verify(it._p - 1, _last);
      T* cur = _last;
      while (cur > it._p) {
        _alloc.construct(cur, *(cur - 1));
        _alloc.destroy(cur - 1);
        --cur;
      }
      _alloc.construct(cur, val);
      ++_last;
      return Iterator(this, cur);
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
    // 管理有效迭代器对象的链表
    struct Iterator_base {
      Iterator_base(Iterator* it = nullptr, Iterator_base* next = nullptr)
        : _it(it)
        , _next(next)
      {}  
      Iterator* _it; // 迭代器对象的指针
      Iterator_base* _next;
    };
    Iterator_base _head;
    void verify(T* first, T* last) {
      Iterator_base* pre = &_head;
      Iterator_base* cur = _head._next;
      while (cur != nullptr) {
        // 将所有指向[first, last]范围的迭代器进行失效处理
        if (cur->_it->_p > first && cur->_it->_p <= last) {
          cur->_it->_vec = nullptr;
          pre->_next = cur->_next;
          delete cur;
          cur = pre->_next;
        } else {
          pre = cur;
          cur = cur->_next;
        }
      }
    }
  private:
    T* _first;
    T* _last;
    T* _end;
    Alloc _alloc;
};

