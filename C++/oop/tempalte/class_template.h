#pragma once
#include <iostream>

template<class T>
class SeqStack {
  public:
    SeqStack(int size = 5)
      : _stack(new T[size])
      , _top(-1)
      , _size(size)
  {}
    ~SeqStack() {
      delete[] _stack;
    }
    SeqStack(const SeqStack<T>& s) 
      : _top(s._top) 
      , _size(s._size)
    {
      T* newStack = new T[s._size];
      for (int i = 0; i <= s._top; ++i) {
        newStack[i] = s._stack[i];
      }
      _stack = newStack;
    }
    SeqStack<T>& operator=(const SeqStack<T>& s) {
      if (this == &s) {
        return *this;
      }
      delete[] _stack;
      T* newStack = new T[s._size];
      for (int i = 0; i <= s._top; ++i) {
        newStack[i] = s._stack[i];
      }
      _stack = newStack;
      _top = s._top;
      _size = s._size;
    }

    void push(const T& e) {
      if (full()) {
        increment();
      }
      _stack[++_top] = e;
    }
    void pop() {
      if (empty()) {
        return;
      }
      --_top;
    }
    T top() const {
      return _stack[_top];
    }
    bool full() {
      return _top == _size - 1;
    }
    bool empty() {
      return _top == -1;
    }
  private:
    void increment() {
      int newsize = _size * 2;
      T* newStack = new T[newsize];
      for (int i = 0; i <= _top; ++i) {
        newStack[i] = _stack[i];
      }
      delete[] _stack;
      _stack = newStack;
      _size *= 2;
    }
  private:
    T* _stack;
    int _top;
    int _size;
};
