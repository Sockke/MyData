#include <iostream>
#include <atomic>
using namespace std;

#if 0
template <class T>
class Unique_ptr {
  public:
    Unique_ptr(T* ptr)
      : _ptr(ptr)
    {}
    ~Unique_ptr() {
      if (_ptr != nullptr) {delete _ptr;}
    }
    Unique_ptr(Unique_ptr<T>&& up)
      : _ptr(up.release())
    {}
    Unique_ptr<T>& operator=(Unique_ptr<T>&& up) {
      if (this != &up) {
        if (_ptr != nullptr) {delete _ptr;}
        _ptr = up.release();
      }
      return *this;
    }
    T& operator*() const {return *_ptr;}
    T* operator->() const {return _ptr;}
  private: 
    T* release() {
      T* tmp = _ptr;
      _ptr = nullptr;
      return tmp;
    }
    Unique_ptr(const Unique_ptr<T>&) = delete;
    Unique_ptr<T>& operator=(const Unique_ptr<T>&) = delete;

    T* _ptr;
};

template<class T>
struct RefCnt {
  public: 
    RefCnt(T* ptr = nullptr)
      : _ptr(ptr)
    {
      if (_ptr != nullptr) {_cnt = 1;}
    }
    void addCnt() {++_cnt;}
    int subCnt() {return --_cnt;}
  private:
    T* _ptr;
    atomic_int _cnt;
};
template <class T>
class Shared_ptr {
  public:
    Shared_ptr(T* ptr = nullptr)
      : _ptr(ptr)
    {
      _refCnt = new RefCnt<T>(ptr);
    }
    ~Shared_ptr() {
      if (_refCnt->subCnt() == 0) {delete _ptr;}
    }
    Shared_ptr(const Shared_ptr<T>& sp) 
      : _ptr(sp._ptr)
      , _refCnt(sp._refCnt)
    {
      if (sp._ptr != nullptr) {_refCnt->addCnt();}
    }
    Shared_ptr<T>& operator=(const Shared_ptr<T>& sp) {
      if (this != &sp) {
        if (_refCnt->subCnt() == 0)  {delete _ptr;}
        _ptr = sp._ptr;
        _refCnt = sp._refCnt;
        if (_ptr != nullptr) {_refCnt->addCnt();}
      }
    }
    T& operator*() const {return *_ptr;}
    T* operator->() const {return _ptr;}
  private:
    T* _ptr;
    RefCnt<T>* _refCnt;
};

int main() {
  Shared_ptr<int> p1(new int);
  Shared_ptr<int> p2(p1);
  Shared_ptr<int> p3;
  p3 = p1;
  
  *p1 = 20;
  cout << *p2 << endl;
  cout << *p3 << endl;
  return 0;
}
#endif

template <class T>
class Unique_ptr {
  public:
    Unique_ptr(T* ptr)
      : _ptr(ptr)
    {}
    ~Unique_ptr() {
      if (_ptr != nullptr) {delete _ptr;}
    }
    Unique_ptr(Unique_ptr<T>&& uptr) 
      : _ptr(uptr.release())
    {}
    Unique_ptr<T>& operator=(Unique_ptr<T>&& uptr) {
      if (*this == uptr) {return *this;}
      _ptr = uptr.release();
      return *this;
    }
    T& operator*() {
      return *_ptr;
    }
    T* operator->() const {
      return _ptr;
    }
  private:
    T* release() {
      T* tmp = _ptr;
      _ptr = nullptr;
      return tmp;
    }
    Unique_ptr(const Unique_ptr<T>&) = delete;
    Unique_ptr<T>& operator=(const Unique_ptr<T>&) = delete;
    T* _ptr;
};

template <class T>
class RefCnt {
  public:
    RefCnt(T* ptr)
      : _ptr(ptr)
    {
      if (_ptr != nullptr) {_cnt = 1;}
    }
    void addCnt() {++_cnt;}
    int subCnt() {--_cnt; return _cnt;}
  private:
    T* _ptr;
    atomic_int _cnt;
};

template <class T>
class Shared_ptr {
  public:
    Shared_ptr(T* ptr)
      : _ptr(ptr)
    {
      _refcnt = new RefCnt<T>(ptr);
    }
    ~Shared_ptr() {
      if (_refcnt->subCnt() == 0) {
        delete _ptr;
      }
    }
    Shared_ptr(const Shared_ptr<T>& sptr) 
      : _ptr(sptr._ptr)
      , _refcnt(sptr._refcnt) 
    {
      if (_ptr != nullptr) {
        _refcnt->addCnt();
      }
    }
    Shared_ptr<T>& operator=(const Shared_ptr<T>& sptr) {
      if (*this == sptr) {return *this;}
      if (_refcnt->subCnt() == 0) {
        delete _ptr;
      }
      _ptr = sptr._ptr;
      _refcnt = sptr._refcnt;
      _refcnt->addCnt();
    }

    T& operator*() {
      return *_ptr;
    } 
    T* operator->() const {
      return _ptr;
    }
  private:

    T* _ptr;
    RefCnt<T>* _refcnt;
};

int main() {
  Shared_ptr<int> sptr(new int);
  Shared_ptr<int> sptr2(sptr);
  *sptr2 = 10;
  cout << *sptr << endl;
  return 0;
}
