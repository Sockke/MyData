#pragma once
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class BSTree {
  public:
    BSTree() : _root(nullptr) {}
    ~BSTree() {}
    void insert(const int& data) {
      if (_root == nullptr) {
        _root = new Node(data);
        return;
      }
      Node* parent = nullptr;
      Node* cur = _root;
      while (cur != nullptr) {
        if (data == cur->_data) {
          return;
        } else if (data < cur->_data) {// 左子树
          parent = cur;
          cur = cur->_left;
        } else { // 右子树
          parent = cur;
          cur = cur->_right;
        }
      }
      if (data < parent->_data) {
        parent->_left = new Node(data);
      } else {
        parent->_right = new Node(data);
      }
    }
    // 前序遍历
    void preOrder_r() const {
      preOrder_r(_root);
      cout << endl;
    }
    // 中序遍历
    void inOrder_r() const {
      inOrder_r(_root);
      cout << endl;
    }

    /*
      BST区间搜索
    */
    void interval_search(vector<int>& vec, int left, int right) {
      interval_search(_root, vec, left, right);
    }


    /*
      LCA问题: latest common ancient
      求BST中的最近公共祖先
    */
    int getLCA(int data1, int data2) {
      Node* common = getLCA(_root, data1, data2);
      if (common == nullptr) {
        throw "no common ancient";
      }
      return common->_data;
    }

  private:
    struct Node {
      Node(const int& data)
        : _data(data)
        , _left(nullptr)
        , _right(nullptr) 
      {}
      int _data;
      Node* _left;
      Node* _right;
    };

    // 前序遍历
    void preOrder_r(Node* node) const {
      if (node != nullptr) {
        cout << node->_data << " ";
        preOrder_r(node->_left);
        preOrder_r(node->_right);
      }
    }
    // 中序遍历
    void inOrder_r(Node* node) const {
      if (node != nullptr) {
        inOrder_r(node->_left);
        cout << node->_data << " ";
        inOrder_r(node->_right);
      }
    }

    // 区间搜索递归代码
    // 对于满足区间内的再进行递归, 不满足的就不递归
    // 从而达到区间搜索的效果
    void interval_search(Node* node, vector<int>& vec, int left, int right) {
      if (node != nullptr) {
        if (node->_data > left) {
          interval_search(node->_left, vec, left, right);
        }
        if (node->_data >= left && node->_data <= right) {
          vec.push_back(node->_data);
        }
        if (node->_data < right) {
          interval_search(node->_right, vec, left, right);
        }
      }
    }


    // 获取BST中两个值的公共祖先问题递归代码
    // 求两个值的公共祖先,
    // 如果两个值不再同一个分支, 那么公共祖先的值在这两个值之间
    // 如果两个值在同一分支, 那么公共祖先的值是这两个值其中一个
    Node* getLCA(Node* node, int data1, int data2) {
      // 没有找到公共祖先
      if (node == nullptr) {
        return nullptr;
      }
      // 两个值都小于当前节点, 说明公共祖先在左子树
      if (data1 < node->_data && data2 < node->_data) {
        return getLCA(node->_left, data1, data2);
      }
      // 两个值都大于当前节点, 说明公共祖先在右子树
      if (data1 > node->_data && data2 > node->_data) {
        return getLCA(node->_right, data1, data2);
      }
      // 当前节点的值在两个值中间或等于其中一个值
      return node;
    }


    Node* _root;
};
