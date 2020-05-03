#include <cstring>

template<class T>
bool myCompare(T a, T b) {
  return a > b;
}

//template bool myCompare(int a, int b);

//template<>
//bool myCompare<const char*>(const char* a, const char* b) {
//  return strcmp(a, b) > 0;
//}

//template<class T>
//class Tmp {
//  public:
//    Tmp(const T& a = 10)
//      : _a(a)
//    {}
//    T getA() {
//      return _a;
//    }
//    T _a;
//};

