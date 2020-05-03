#pragma once
#include <iostream>

template<class T>
class Queue {
  public:
    Queue() {
      _rear = _front = new QueueNode();
    }
    ~Queue() {
      QueueNode* cur = _front;
      while (cur != nullptr) {
        _front = cur->_next;
        delete cur;
        cur = _front;
      }
    }
    void push(const T& data) {
      QueueNode* qNode = new QueueNode(data);
      _rear->_next = qNode;
      _rear = qNode;
    }
    void pop() {
      if (empty()) {
        return;
      }
      QueueNode* del = _front->_next;
      _front->_next = del->_next;
      delete del;
      if (_front->_next == nullptr) {
        _rear = _front;
      }
    }
    T front() const {
      return _front->_next->_data;
    }
    bool empty() const {
      return _front == _rear;
    }
  private:
    struct QueueNode {
      QueueNode(const T& data = T(), QueueNode* next = nullptr)
        : _data(data)
        , _next(next)
      {}
      // 编译器默认视为static
      void* operator new(size_t size) {
        // 先判断对象池是否为空, 如果为空则进行new开辟并构造空间
        if (_nodePool == nullptr) {
          // 开辟连续的以QueueNode为单位的空间
          _nodePool = (QueueNode*)new char[POOL_SIZE * sizeof(QueueNode)];
          // 将所有的QueueNode连接起来
          QueueNode* cur = _nodePool;
          while (cur < _nodePool + POOL_SIZE - 1) {
            cur->_next = cur + 1;
            cur = cur->_next;
          }
          cur->_next = nullptr;
        }
        // 获取第一个空结点的指针
        QueueNode* getNode = _nodePool;
        // 更新对象池的起始位置
        _nodePool = _nodePool->_next;
        // 返回这块空结点的地址, 来进行构造
        return getNode;
      }
      void operator delete(void* ptr) {
        // 获取要移除的结点的指针
        QueueNode* delNode = (QueueNode*)ptr;
        // 将该移除的结点指针重新连接到对象池的头部
        delNode->_next = _nodePool;
        // 更新对象池的起始位置
        _nodePool = delNode;
      }
      T _data; 
      QueueNode* _next;

      static QueueNode* _nodePool; // 对象池, 指向第一个为空的结点地址
      static const int POOL_SIZE = 10000;
    };
    QueueNode* _front; // 指向队头, 队头是一个头结点
    QueueNode* _rear; // 指向队尾
};
template<class T>
typename Queue<T>::QueueNode* Queue<T>::QueueNode::_nodePool = nullptr;
