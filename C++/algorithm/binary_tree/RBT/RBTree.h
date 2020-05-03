#pragma once
#include <iostream>

using namespace std;

template <class T>
class RBTree {
  public:
    RBTree() : _root(nullptr) {}
    ~RBTree() {}
    /*
      RBT的插入操作, 与BST一样, 只不过插入节点后判断是否需要调整,
      调整主要看叔叔节点, 总共为3种情况:
      1. 叔叔为红色, 将父亲与叔叔节点改为黑色, 爷爷节点改为红色
      2. 叔叔为黑色, 且插入节点与父节点在同一个方向
      将父亲改为黑色, 爷爷改为红色, 然后进行旋转
      3. 叔叔为黑色, 且插入节点与父节点不在同一个方向
      先旋转使得插入节点与父节点在同一方向,
      然后就是情况2
    */
    void insert(const T& data) {
      if (_root == nullptr) {
        // 根节点必须是黑色
        _root = new Node(data, BLACK);
        return;
      }
      Node* parent = nullptr; 
      Node* cur = _root;
      while (cur != nullptr) {
        if (data < cur->_data) { // 左子树
          parent = cur;
          cur = cur->_left;
        } else if (data > cur->_data) { // 右子树
          parent = cur;
          cur = cur->_right;
        } else { // 存在就不用插入了
          return;
        }
      }
      // 判断一下是插入哪一边
      Node* node = new Node(data);
      node->_parent = parent;
      if (data < parent->_data) { // 左孩子
        parent->_left = node; 
      } else { // 右孩子
        parent->_right = node;
      }
      // 判断红黑树是否满足性质
      if (getColor(node->_parent) == RED) {
        // 不满足性质, 需要调整
        insertAdjust(node);
      }
    }
    /*
      RBT的删除操作, 与BST的删除类似, 但是要考虑删除节点后不满足红黑树性质的情况
      如果删除节点为黑色, 那么肯定会破坏红黑树性质, 需要进行调整:
      1. 孩子节点为红色, 直接改为黑色, 调整完毕
      2. 孩子节点为黑色, 需要向兄弟节点借, 分为4种情况:
        1. 兄弟节点为黑色, 兄弟节点同侧孩子为红色
        2. 兄弟节点为黑色, 兄弟节点同侧孩子为黑色, 异侧孩子为红色
        3. 兄弟节点为黑色, 兄弟节点两侧孩子都为黑色
        4. 兄弟节点为红色
    */
    void remove(const T& data) {
      if (_root == nullptr) {
        return;
      }
      Node* cur = _root;
      while (cur != nullptr) {
        if (data < cur->_data) { // 左子树
          cur = cur->_left;
        } else if (data > cur->_data) { // 右子树
          cur = cur->_right;
        } else {
          break; // 找到了
        }
      }

      if (cur == nullptr) { // 没找到
        return;
      }

      // 先判断第2种情况, 删除节点有2个孩子
      if (cur->_left != nullptr && cur->_right != nullptr) {
        // 找前驱节点 
        Node* pre = cur->_left;
        while (pre->_right != nullptr) {
          pre = pre->_right;
        }
        cur->_data = pre->_data;
        cur = pre; // 更新被删除节点
      }
      // 第1种情况, 删除节点有1个或没有孩子
      Node* child = cur->_left;
      if (child == nullptr) {
        child = cur->_right;
      }
      if (cur->_parent == nullptr) { // 根节点
        delete cur;
        _root = child;
        setColor(_root, BLACK);
        return;
      }

      if (child != nullptr) {
        child->_parent = cur->_parent; 
        if (cur == cur->_parent->_left) { // 左孩子
          cur->_parent->_left = child;
        } else { //右孩子
          cur->_parent->_right = child; 
        }
        // 获取删除节点的颜色
        Color c = getColor(cur); 
        delete cur;
       
        // 如果删除节点为黑色, 那么需要调整
        if (c == BLACK) {
          removeAdjust(child);
        }
      } else {
        if (getColor(cur) == BLACK)  {
          removeAdjust(cur);
        }
        if (cur == cur->_parent->_left) {
          cur->_parent->_left = nullptr;
        } else {
          cur->_parent->_right= nullptr;
        }
        delete cur;
      }
    }

    void levelOrder_r() const {
      int h = high(_root);
      for (int i = 1; i <= h; ++i) {
        cout << "第" << i << "层:";
        levelOrder_r(_root, i);
        cout << endl;
      }
      cout << endl;
    }
  private:
    enum Color {
      RED,
      BLACK
    };
    struct Node {
      Node(const T& data, Color color = RED)
        : _data(data)
        , _color(color)
        , _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
      {}
      T _data;
      Color _color;
      Node* _left;
      Node* _right;
      Node* _parent;
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

    // 获取节点颜色
    Color getColor(Node* node) {
      return node == nullptr ? BLACK : node->_color;
    }
    // 设置节点颜色
    void setColor(Node* node, Color color) {
      node->_color = color;
    }

    // 右旋
    void rightRotate(Node* node) {
      Node* child = node->_left; 
      child->_parent = node->_parent;
      // 判断node是否是根节点
      if (node->_parent == nullptr) { 
        _root = child;
      } else { 
        // 判断node在左子树还是右子树
        if (node == node->_parent->_left) {  // 左子树
          node->_parent->_left = child;
        } else { // 右子树
          node->_parent->_right = child;
        }
      }

      node->_left = child->_right;
      if (child->_right != nullptr) {
        child->_right->_parent = node;
      }

      child->_right = node;
      node->_parent = child;
    }

    // 左旋
    void leftRotate(Node* node) {
      Node* child = node->_right;
      child->_parent = node->_parent;
      if (node->_parent == nullptr) {
        _root = child;
      } else {
        if (node == node->_parent->_left) { // 左子树
          node->_parent->_left = child; 
        } else { // 右子树
          node->_parent->_right = child;
        }
      }

      node->_right = child->_left;
      if (child->_left != nullptr) {
        child->_left->_parent = node;
      }

      child->_left = node;
      node->_parent = child;
    }

    // 插入调整
    void insertAdjust(Node* node) {
      while (getColor(node->_parent) == RED) {
        // 找到叔叔的位置
        if (node->_parent == node->_parent->_parent->_left) {
          // 父亲在左子树, 那么叔叔就在右子树
          Node* uncle = node->_parent->_parent->_right;
          // 第1种情况, 叔叔为红色
          if (getColor(uncle) == RED) {
            setColor(node->_parent, BLACK);
            setColor(uncle, BLACK);
            setColor(node->_parent->_parent, RED);
            node = node->_parent->_parent; // 继续调整
          } else { // 第2, 3种情况
            // 先判断第3种情况
            if (node == node->_parent->_right) {
              // 左旋
              leftRotate(node->_parent);
              node = node->_left; // 找回node的位置
            }
            // 第2种情况
            setColor(node->_parent, BLACK);
            setColor(node->_parent->_parent, RED);
            // 右旋
            rightRotate(node->_parent->_parent);
            break;
          }
        } else {
          // 父亲在右子树, 那么叔叔就在左子树
          Node* uncle = node->_parent->_parent->_left;
          // 第1种情况, 叔叔为红色
          if (getColor(uncle) == RED) {
            setColor(node->_parent, BLACK);
            setColor(uncle, BLACK);
            setColor(node->_parent->_parent, RED);
            node = node->_parent->_parent; // 继续调整
          } else { // 第2, 3种情况
            // 先判断第3种情况
            if (node == node->_parent->_left) {
              // 右旋
              rightRotate(node->_parent);
              node = node->_right; // 找回node的位置
            }
            // 第2种情况
            setColor(node->_parent, BLACK);
            setColor(node->_parent->_parent, RED);
            // 左旋
            leftRotate(node->_parent->_parent);
            break;
          }
        }
      }
      // 根节点的颜色始终为黑色, 因此调整过程中可能存在将根节点调整成红色了
      setColor(_root, BLACK);
    }

    // 删除调整
    void removeAdjust(Node* node) {
      // 调整节点为黑色, 有4种情况
      while (node != _root && getColor(node) == BLACK) {
        if (node == node->_parent->_left) { // 调整节点在左子树
          Node* brother = node->_parent->_right;
          // 先判断第4种情况, 兄弟节点为红色
          if (getColor(brother) == RED) {
            setColor(node->_parent, RED);
            setColor(brother, BLACK);
            leftRotate(node->_parent);
            brother = node->_parent->_right;
          }
          // 判断第3种情况
          if (getColor(brother->_left) == BLACK
              && getColor(brother->_right) == BLACK) {
            setColor(brother, RED);
            node = node->_parent;
          } else { // 判断第1, 2种情况
            if (getColor(brother->_right) != RED) { // 第2种情况
              setColor(brother, RED);
              setColor(brother->_left, BLACK);
              rightRotate(brother);
              brother = node->_parent->_right;
            } 
            // 第1种情况
            setColor(brother, getColor(node->_parent));
            setColor(node->_parent, BLACK);
            setColor(brother->_right, BLACK);
            leftRotate(node->_parent);
            break;
          }
        } else { // 调整节点在右子树
          Node* brother = node->_parent->_left;
          // 先判断第4种情况, 兄弟节点为红色
          if (getColor(brother) == RED) {
            setColor(node->_parent, RED);
            setColor(brother, BLACK);
            rightRotate(node->_parent);
            brother = node->_parent->_left;
          }
          // 判断第3种情况
          if (getColor(brother->_left) == BLACK
              && getColor(brother->_right) == BLACK) {
            setColor(brother, RED);
            node = node->_parent;
          } else { // 判断第1, 2种情况
            if (getColor(brother->_left) != RED) { // 第2种情况
              setColor(brother, RED);
              setColor(brother->_right, BLACK);
              leftRotate(brother);
              brother = node->_parent->_left;
            } 
            // 第1种情况
            setColor(brother, getColor(node->_parent));
            setColor(node->_parent, BLACK);
            setColor(brother->_left, BLACK);
            rightRotate(node->_parent);
            break;
          }
        }
      }
      // 调整节点为红色, 直接该为黑色即可
      setColor(node, BLACK);
    }

    // 递归层序遍历
    void levelOrder_r(Node* node, int h)  const {
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
