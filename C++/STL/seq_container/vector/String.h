#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class String {
  public:
    String(const char* str = nullptr) {
      cout << "String(const char*)" << endl;
      if (str != nullptr) {
        int len = strlen(str);
        _str = new char[len + 1];
        strcpy(_str, str);
      } else {
        _str = new char[1];
        _str[0] = '\0';
      }
    }
    ~String() {
      cout << "~String()" << endl;
      if (_str) {
        delete[] _str;
      }
    }
    String(const String& s) {
      cout << "String(const String&)" << endl;
      int len = strlen(s._str);
      _str = new char[len + 1];
      strcpy(_str, s._str);
    }
    String& operator=(const String& s) {
      cout << "operator=(const String&)" << endl;
      if (this == &s) {
        return *this;
      }
      delete[] _str;
      int len = strlen(s._str);
      _str = new char[len + 1];
      strcpy(_str, s._str);
      return *this;
    }
    String(String&& s) {
      cout << "String(String&&)" << endl;
      _str = s._str;
      s._str = nullptr;
    }
    String& operator=(String&& s) {
      cout << "operator=(String&&)" << endl;
      if (this == &s) {
        return *this;
      }
      delete[] _str;
      _str = s._str;
      s._str = nullptr;
      return *this;
    }
    const char* c_str() const {
      return _str;
    }
  private:
    char* _str;
    friend String operator+(const String& left, const String& right);
    friend std::ostream& operator<<(std::ostream& out, const String& s);
};

String operator+(const String& left, const String& right) {
  String tmp; // 构建临时对象, 开辟内存, 拷贝数据然后返回
  delete[] tmp._str;
  tmp._str = new char[strlen(left._str) + strlen(right._str) + 1];
  strcpy(tmp._str, left._str);
  strcat(tmp._str, right._str);
  return tmp;
}
std::ostream& operator<<(std::ostream& out, const String& s) {
  out << s._str;
  return out;
}
