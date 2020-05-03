#pragma once
#include <iostream>
#include <cstring>

// 实现简单的string, 不带迭代器

class String {
  public:
    String(const char* str = nullptr) {
      if (str != nullptr) {
        int len = strlen(str);
        _str = new char[len + 1];
        strcpy(_str, str);
      } else {
        _str  = new char[1];
        *_str = '\0';
      }
    }
    ~String() {
      delete[] _str;
    }
    String(const String& s) {
      int len = strlen(s._str);
      _str = new char[len + 1];
      strcpy(_str, s._str);
    }
    String& operator=(const String& s) {
      if (this == &s) {
        return *this;
      }
      delete[] _str;
      int len = strlen(s._str);
      _str = new char[len + 1];
      strcpy(_str, s._str);
      return *this;
    }
    // 比较运算符
    bool operator>(const String& s) const {
      return strcmp(_str, s._str) > 0;
    }
    bool operator<(const String& s) const {
      return strcmp(_str, s._str) < 0;
    }
    bool operator==(const String& s) const {
      return strcmp(_str, s._str) == 0;
    }
    // 方括号运算符[]
    char& operator[](int index) {
      return _str[index];
    }
    const char& operator[](int index) const {
      return _str[index];
    }
    // c_str
    const char* c_str() const {
      return _str;
    }
    // length/size
    int length() const {
      return strlen(_str);
    }
  private:
    friend String operator+(const String& s1, const String& s2);
    friend std::ostream& operator<<(std::ostream& ost, const String& s);
  private:
    char* _str;
};

String operator+(const String& s1, const String& s2) {
  //char* newstr = new char[strlen(s1._str) + strlen(s2._str) + 1];
  //strcpy(newstr, s1._str);
  //strcat(newstr, s2._str);
  //String tmp(newstr);
  //delete[] newstr;
  //return tmp;
  String tmp;
  delete[] tmp._str;
  tmp._str = new char[strlen(s1._str) + strlen(s2._str) + 1];
  strcpy(tmp._str, s1._str);
  strcat(tmp._str, s2._str);
  return tmp;
}

std::ostream& operator<<(std::ostream& ost, const String& s) {
  ost << s._str;
  return ost;
}
