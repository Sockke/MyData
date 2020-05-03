#pragma once
#include <iostream>

// 实现简单的循环队列, 留一个空位
// 也可以加上计数器, 这样可以充分利用循环队列的空间
class Queue {
  public:
    Queue(int size = 5) {
      _queue = new int[size];
      _front = 0;
      _rear = 0;
      _size = 5;
    }
    // 拷贝构造
    Queue(const Queue& q) {
      _queue = new int[q._size];
      for (int i = q._front; i != q._rear; i = (i + 1) % q._size) {
        _queue[i] = q._queue[i];
      }
    }
    // 赋值重载
    Queue& operator=(const Queue& q) {
      if (this == &q)  {
        return *this;
      }

      delete[] _queue;

      _queue = new int[q._size];
      for (int i = q._front; i != q._rear; i = (i + 1) % q._size) {
        _queue[i] = q._queue[i];
      }
      return *this;
    }
    ~Queue() {
      delete[] _queue;
    }

    void push(int e) {
      if (full()) {
        increment();
      }
      _queue[_rear] = e;
      _rear = (_rear + 1) % _size;
    }
    void pop() {
      if (empty()) {
        return;
      }
      _front = (_front + 1) % _size;
    }
    int front() {
      return _queue[_front];
    }
    bool full() {
      return (_rear + 1) % _size == _front;
    }
    bool empty() {
      return _front == _rear;
    }
  private:
    void increment() {
      int* newQueue = new int[_size * 2];
      int index = 0;
      for (int i = _front; i != _rear; i = (i + 1) % _size) {
        newQueue[index++] = _queue[i];
      }
      delete[] _queue;
      _queue = newQueue;
      _front = 0;
      _rear = index;
      _size *= 2;
    }
  private:
    int* _queue;
    int _front; // 指向队头元素
    int _rear; // 指向队尾空位
    int _size; // 队列大小
};
