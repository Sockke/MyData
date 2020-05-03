#include <iostream>
#include <memory>

template<class T, class D = std::default_delete<T>>
class UniquePtr {
  public:
    UniquePtr(T* uptr = nullptr, D del = D())
      : _uptr(uptr), _del(del) {}
    UniquePtr(UniquePtr<T>&& uniquePtr) {
      _uptr = uniquePtr._uptr;  // 临时对象管理的资源转移
      uniquePtr._uptr = nullptr;  // 临时对象变量置空
    }
    UniquePtr<T>& operator=(UniquePtr<T>&& uniquePtr) {
      if (_uptr != nullptr) {  // 释放当前智能指针管理的资源
        delete _uptr;
      }
      _uptr = uniquePtr._uptr;  // 临时对象管理的资源转移
      uniquePtr._uptr = nullptr;  // 临时对象变量置空
    }
    // 重载*
    T& operator*() const {
      return *_uptr;
    }
    // 重载->
    T* operator->() const {
      return _uptr;
    }
    ~UniquePtr() {
      if (_uptr != nullptr) {
        std::cout << "~UniquePtr" << std::endl;
        //delete _uptr;
        _del(_uptr);
      }
    }
  private:
    mutable T* _uptr;
    D _del;
};
