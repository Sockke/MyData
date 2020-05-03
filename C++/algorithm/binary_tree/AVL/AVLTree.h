#pragma once
#include <iostream>
using namespace std;

template <class T>
class AVLTree {
  public:
    AVLTree() : _root(nullptr) {}
    ~AVLTree() {}
    /*
      AVL插入, 与BST插入类似
      但是需要在回溯的时候, 判断节点的平衡
      并且更新节点的高度
    */
    void insert_r(const T& data) {
      _root = insert_r(_root, data);
    }
    /*
      AVL删除  , 与BST删除类似
      但是需要在
    */ 
    void remove_r(const T& data) {
      _root = remove_r(_root, data);
    }
    void levelOrder_r() const {
      int h = high(_root);
      for (int i = 1; i <= h; ++i) {
        levelOrder_r(_root, i);
      }
      cout << endl;
    }
  private:
    struct Node {
      Node(const T& data)
        : _data(data)
        , _left(nullptr)
        , _right(nullptr)
        , _height(1)
      {}
      T _data;
      Node* _left;
      Node* _right;
      int _height;
    };
    // 树的高度
    int high(Node* node) const {
      if (node == nullptr) {
        return 0;
      }
      int left = high(node->_left);
      int right = high(node->_right);
      return max(left, right) + 1;
    }
    // 节点的高度
    int height(Node* node) const {
      return node == nullptr ? 0 : node->_height;
    }

    /*
      AVL旋转平衡问题, 总共有4种情况
      1. 左孩子的左子树太高, 通过右旋
      2. 右孩子的右子树太高, 通过左旋
      3. 左孩子的右子树太高, 先以孩子为根节点左旋变成第1种情况, 然后再右旋
      4. 右孩子的左子树太高, 先以孩子为根节点右旋变成第3种情况, 然后在左旋
    */
    // 右旋
    Node* rightRotate(Node* node) {
      Node* child = node->_left; 
      node->_left = child->_right;  // 挂节点
      child->_right = node;  // 旋转
      node->_height = max(height(node->_left), height(node->_right)) + 1;
      child->_height = max(height(child->_left), height(child->_right)) + 1;
      return child; // 返回根节点
    }
    // 左旋
    Node* leftRotate(Node* node) {
      Node* child = node->_right; 
      node->_right = child->_left; // 挂节点
      child->_left = node; // 旋转
      node->_height = max(height(node->_left), height(node->_right)) + 1;
      child->_height = max(height(child->_left), height(child->_right)) + 1;
      return child; // 返回根节点
    }
    // 左-右旋, 左平衡
    Node* leftBalance(Node* node) {
      node->_left = leftRotate(node->_left);
      return rightRotate(node);
    }
    // 右-左旋, 右平衡
    Node* rightBalance(Node* node) {
      node->_right = rightRotate(node->_right);
      return leftRotate(node);
    }

    // AVL的插入
    Node* insert_r(Node* node, const T& data) {
      if (node == nullptr) {
        return new Node(data);
      }
      if (data == node->_data) {
        return node;
      }
      if (data < node->_data) { // 左子树
        node->_left = insert_r(node->_left, data);
        // 回溯时, 判断node是否失衡
        if (height(node->_left) - height(node->_right) > 1) {
          // 左孩子的左子树太高
          if (height(node->_left->_left) >= height(node->_left->_right)) {
            node = rightRotate(node);
          } else { // 左孩子的右子树太高
            node = leftBalance(node);
          }
        }
      } else { // 右子树
        node->_right = insert_r(node->_right, data);
        // 回溯时, 判断node是否失衡
        if (height(node->_right) - height(node->_left) > 1) {
          // 右孩子的右子树太高
          if (height(node->_right->_right) >= height(node->_right->_left)) {
            node = leftRotate(node);
          } else { // 右孩子的左子树太高
            node = rightBalance(node);
          }
        }
      }
      // 更新树的高度
      node->_height = max(height(node->_left), height(node->_right)) + 1;
      return node;
    }

    // AVL删除
    Node* remove_r(Node* node, const T& data) {
      if (node == nullptr) {
        return nullptr;
      }
      if (data == node->_data) { // 找到该节点
        // 先判断第2种情况, 也就是被删除节点有2个孩子
        if (node->_left != nullptr && node->_right != nullptr) {
          // 防止失衡当前节点失衡, 删除前驱和后继中高度最高的
          if (height(node->_left) >= height(node->_right)) { // 删除前驱
            Node* pre = node->_left;
            while (pre->_right != nullptr) {
              pre = pre->_right;
            }
            node->_data = pre->_data; // 替换删除节点
            node->_left = remove_r(node->_left, pre->_data); // 删除前驱节点
          } else { // 删除后继
            Node* post = node->_right; 
            while (post->_left != nullptr) {
              post = post->_left;
            }
            node->_data = post->_data;
            node->_right = remove_r(node->_right, post->_data);
          }
        } else { // 第1种情况, 被删除节点没有孩子, 或只有1个孩子
          Node* child = node->_left; 
          if (child == nullptr) {
            child = node->_right;
          }
          // 删除节点
          delete node; 
          return child;
        }
      } else if (data < node->_data) { // 左子树
        node->_left = remove_r(node->_left, data);
        // 回溯时, 判断是否失衡
        if (height(node->_right) - height(node->_left) > 1) {
          // 右孩子的右子树高
          if (height(node->_right->_right) >= height(node->_right->_left)) {
            node = leftRotate(node);
          } else { // 右孩子的左子树高
            node = rightBalance(node);
          }
        }
      } else { // 右子树
        node->_right = remove_r(node->_right, data);
        // 回溯时, 判断是否失衡
        if (height(node->_left) - height(node->_right) > 1) {
          // 左孩子的左子树太高
          if (height(node->_left->_left) >= height(node->_left->_right)) {
            node = rightRotate(node);
          } else { // 左孩子的右子树太高
            node = leftBalance(node);
          }
        }
      }

      // 更新树的高度
      node->_height = max(height(node->_left), height(node->_right)) + 1;

      return node;
    }

    void levelOrder_r(Node* node, int h) const {
      if (node == nullptr) {
        return;
      }
      if (h == 1) {
        cout << node->_data << " ";
      }
      levelOrder_r(node->_left, h - 1);
      levelOrder_r(node->_right, h - 1);
    }

    Node* _root;
};

