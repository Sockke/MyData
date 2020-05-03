#pragma once
#include <iostream>
#include <cstring>

class String {
  public:
    String(const char* str = nullptr) {
      if (str != nullptr) {
        int len = strlen(str);
        _str = new char[len + 1];
        strcpy(_str, str);
      } else {
        _str = new char[1];
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
    bool operator>(const String& s) {
      return strcmp(_str, s._str) > 0;
    }
    bool operator<(const String& s) {
      return strcmp(_str, s._str) < 0;
    }
    bool operator==(const String& s) {
      return strcmp(_str, s._str) == 0;
    }
    // []运算符
    char& operator[](int index) {
      return _str[index];
    }
    const char& operator[](int index) const {
      return _str[index];
    }
    // 其他成员方法
    const char* c_str() const {
      return _str;
    } 
    int length() const {
      return strlen(_str);
    }
    // 迭代器
    class Iterator {
      public:
        Iterator(char* p)
          : _p(p)
        {}
        // !=
        bool operator!=(const Iterator& it) {
          return _p != it._p;
        }
        // *
        char& operator*() {
          return *_p;
        }
        const char& operator*() const {
          return *_p;
        }
        // ->
        char* operator->() const {
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
        char* _p;
    };
    // 返回容器底层首元素的迭代器
    Iterator begin() {
      return Iterator(_str);
    }
    Iterator begin() const { 
      return Iterator(_str);
    }
    // 返回容器底层末尾元素的后继迭代器
    Iterator end() {
      return Iterator(_str + length());
    }
    Iterator end() const {
      return Iterator(_str + length());
    }
  private:
    friend String operator+(const String& s1, const String& s2);
    friend std::ostream& operator<<(std::ostream& ost, const String& s);
  private:
    char* _str;
};

String operator+(const String& s1, const String& s2) {
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
