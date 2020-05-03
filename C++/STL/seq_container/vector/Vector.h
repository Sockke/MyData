#include <iostream>
#include <utility>

template <class T>
struct MAllocator {
  // 开辟内存
  T* allocate(size_t size) {
    return (T*)malloc(sizeof(T) * size);
  }
  // 释放内存
  void deallocate(T* ptr) {
    free(ptr);
  }
  // 构造对象, 定位new
  template <class Tp>
  void construct(T* ptr, Tp&& obj) {
    new (ptr) T(std::forward<Tp>(obj));
  }
  // 析构对象
  void destroy(T* ptr) {
    ptr->~T();
  }
};

template <class T, class Alloc = MAllocator<T>>
class Vector {
  public:
    Vector(size_t size) {
      // 开辟内存
      _begin = _alloc.allocate(size);
      _last = _begin; 
      _end = _begin + size;
    }
    ~Vector() {
      // 析构所有对象
      int size = _last - _begin;
      for (size_t i = 0; i < size; ++i) {
        _alloc.destroy(_begin + i);
      }
      // 释放内存
      _alloc.deallocate(_begin);
    }
    Vector(const Vector<T>& obj) {
      int size = obj._last - obj._begin; 
      // 开辟内存
      _begin = _alloc.allocate(size);
      // 构造对象
      for (int i = 0; i < size; ++i) {
        _alloc.construct(_begin + i, obj._begin[i]);
      }
    }
    Vector<T>& operator=(const Vector<T>& obj) {
      if (this == &obj) {
        return *this;
      }
      int size = _last - _begin;
      // 析构对象
      for (int i = 0; i < size; ++i) {
        _alloc.destroy(_begin + i);
      }
      // 释放内存
      _alloc.deallocate(_begin);
      size = obj._last - obj._begin;
      // 开辟内存
      _begin = _alloc.allocate(size);
      // 构造对象
      for (int i = 0; i < size; ++i) {
        _alloc.construct(_begin + i, obj._begin[i]);
      }
      return *this;
    }
    //void push_back(const T& val) {
    //  if (full()) {
    //    expand();
    //  }
    //  _alloc.construct(_last, val);
    //  ++_last;
    //}
    template <class Tp>
    void push_back(Tp&& val) {
      if (full()) {
        expand();
      }
      _alloc.construct(_last, std::forward<Tp>(val));
      ++_last;
    }
    bool full() const {
      return _last == _end;
    }
  private:
    void expand() {
      int size = _last - _begin;
      // 开辟新内存        
      int newsize = 2 * size;
      T* newBegin = _alloc.allocate(newsize);
      // 构造对象
      for (int i = 0; i < size; ++i) {
        _alloc.construct(newBegin + i, _begin[i]);
        // 析构原来的对象
        _alloc.destroy(_begin + i);
      }
      // 释放原来内存
      _alloc.deallocate(_begin);
      _begin = newBegin;
      _end = _begin + newsize;
    }
  private:
    T* _begin;  
    T* _last;
    T* _end;
    Alloc _alloc;
};
