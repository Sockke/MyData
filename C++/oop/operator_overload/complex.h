#pragma once
#include <iostream>
// 实现复数类

class Complex {
  public:
    Complex(int mreal = 0, int mvirtual = 0)
      : _real(mreal)
      , _virtual(mvirtual)
    {}
    ~Complex() {}
    // + 
    Complex operator+(const Complex& com) {
      // 返回构造的新对象
      return Complex(_real + com._real, _virtual + com._virtual);
    }
    // 前置++
    Complex& operator++() {
      ++_real;
      ++_virtual;
      return *this;
    }
    // 后置++
    Complex operator++(int) {
      return Complex(_real++, _virtual++);
    }
    void show() const {
      std::cout << "_real:" << _real << " _virtual:" << _virtual << std::endl;
    }
  private: 
    friend Complex operator+(const Complex& com1, const Complex& com2);
    friend std::ostream& operator<<(std::ostream& ost, const Complex& com);
    friend std::istream& operator>>(std::istream& ist, Complex& com);
  private:
    int _real;
    int _virtual;
};

// 实现20 + Complex()
Complex operator+(const Complex& com1, const Complex& com2) {
  return Complex(com1._real + com2._real, com1._virtual + com2._virtual);
}

std::ostream& operator<<(std::ostream& ost, const Complex& com) {
  ost << "_real:" << com._real << " _virtual:" << com._virtual;
  return ost;
}
std::istream& operator>>(std::istream& ist, Complex& com) {
  ist >> com._real >> com._virtual;
  return ist;
}
