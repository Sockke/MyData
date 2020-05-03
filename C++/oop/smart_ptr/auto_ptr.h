#include <iostream>
#include <memory>

template<class T>
class AutoPtr {
  public:
    AutoPtr(T* aptr = nullptr) : _aptr(aptr) {}
    AutoPtr(const AutoPtr<T>& autoPtr) 
      : _aptr(autoPtr.release()) {}
    AutoPtr<T>& operator=(const AutoPtr<T>& autoPtr)  {
      _aptr = autoPtr.release();
      return *this;
    }
    // 重载*
    T& operator*() const {
      return *_aptr;
    }
    // 重载->    .operator->()->func()
    T* operator->() const {
      return _aptr;
    }
    ~AutoPtr() {
      std::cout << "~AutoPtr" << std::endl;
      if (_aptr != nullptr) {
        delete _aptr;
      }
    }
  private:
    T* release() const {
      T* oldPtr = _aptr;
      _aptr = nullptr;
      return oldPtr;
    }
  private:
    mutable T* _aptr;
};
