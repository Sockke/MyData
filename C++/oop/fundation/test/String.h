#pragma once
#include <iostream>
#include <cstring>

// 实现简单的string
class String {
  public:
    String(const char* str = nullptr) {
      if (str == nullptr) {
        _str = new char[1];
        *_str = '\0';
      } else {
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
      }
    }
    // 拷贝构造
    String(const String& s) {
      _str = new char[strlen(s._str) + 1];
      strcpy(_str, s._str);
    }
    // 赋值重载
    String& operator=(const String& s) {
      if (this == &s) {
        return *this;
      }

      delete[] _str;

      _str = new char[strlen(s._str) + 1];
      strcpy(_str, s._str);
      return *this;
    }
    ~String() {
      delete _str;
    }
  private:
    char* _str;
};
