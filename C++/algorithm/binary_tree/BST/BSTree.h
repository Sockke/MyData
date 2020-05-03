#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/*
  递归的增删:
  对于树结构, 增加或删除会导致节点地址域的更新, 也就是或将孩子节点连接到父节点,
  这个过程在递归代码中的体现就是向上回溯, 将当前节点的地址返回给父节点, 
  让父节点来进行接收
*/

template <class T, class Comp = less<T>>
class BSTree {
  public:
    BSTree(Comp comp = Comp()) 
      : _root(nullptr)
      , _comp(comp)
    {}
    // 利用层序遍历的思想, 来将出队的节点删除
    ~BSTree() {
      if (_root != nullptr) {
        queue<Node*> q;
        q.push(_root);
        while (!q.empty()) {
          Node* cur = q.front();
          q.pop();
          if (cur->_left != nullptr) {
            q.push(cur->_left);
          }
          if (cur->_right != nullptr) {
            q.push(cur->_right);
          }
          delete cur;
        }
      }
    }


    /*
      插入操作:
      满足左孩子<当前节点<右孩子
    */
    void insert(const T& data) {
      // 如果根节点为空
      if (_root == nullptr) {
        _root = new Node(data);
        return;
      }
      Node* parent = nullptr; // 当前节点的父节点
      Node* cur = _root; // 当前节点
      while (cur != nullptr) {
        if (data == cur->_data) {
          return;
        } else if (_comp(data, cur->_data)) { // 左子树
          parent = cur; // 更新当前节点的父节点
          cur = cur->_left;
        } else { // 右子树
          parent = cur; // 更新当前节点的父节点
          cur = cur->_right;
        }
      }
      // 插入当前节点
      if (_comp(data, parent->_data)) { // 左孩子
        parent->_left = new Node(data);
      } else { // 右孩子
        parent->_right = new Node(data);
      }
    }
    // 递归版的插入
    void insert_r(const T& data) {
      _root = insert_r(_root, data);
    }
    /*
    删除操作:
    1. 删除节点没孩子或只有一个孩子, 都需要向删除位置写入地址域
    2. 删除节点有2个孩子, 需要将删除节点的前驱或后继的值覆盖掉删除节点,
    然后转化为删除前驱或后继, 即第一种情况
    */
    void remove(const T& data) {
      if (_root == nullptr) {
        return;
      }
      // 找到需要删除的节点
      Node* parent = nullptr;
      Node* cur = _root;
      while (cur != nullptr) {
        if (data == cur->_data) {
          break; // 找到待删除节点
        } else if (_comp(data, cur->_data)) { // 左子树
          parent = cur;
          cur = cur->_left;
        } else { // 右子树
          parent = cur;
          cur = cur->_right;
        }
      }
      // 没找到删除节点
      if (cur == nullptr) {
        return;
      }
      // 先判断第二种情况, 删除节点有2个孩子
      if (cur->_left != nullptr && cur->_right != nullptr)  {
        // 找到删除节点的前驱
        parent = cur;
        Node* pre = cur->_left;
        while (pre->_right != nullptr) {
          parent = pre;
          pre = pre->_right;
        }
        // 前驱节点覆盖删除节点的值
        cur->_data = pre->_data;
        // 删除前驱节点
        cur = pre;
      }
      // 第一种情况, 只存在删除节点没有孩子或只有一个孩子
      Node* child = cur->_left; // 找到这个孩子, 为空或者不为空
      if (child == nullptr) {
        child = cur->_right;
      }
      if (cur == _root) { // 如果删除节点为根节点
        _root = child;
      } else { // 删除节点不为根节点
        // 向删除节点的位置写入地址域 
        if (cur == parent->_left) { // 左孩子
          parent->_left = child;
        } else { // 右孩子
          parent->_right = child;
        }
      }
      delete cur;
    }
    // 递归版本的删除
    void remove_r(const T& data) {
      _root = remove_r(_root, data);
    }
    /*
      查找操作:
      二分查找的规则进行查找
    */
    bool find(const T& data) const {
      Node* cur = _root;
      while (cur != nullptr) {
        if (data == cur->_data) {
          return true;
        } else if (_comp(data, cur->_data)) {
          cur = cur->_left;
        } else {
          cur = cur->_right;
        }
      }
      return false;
    }
    // 递归版的查询
    bool find_r(const T& data) const {
      return find_r(_root, data) != nullptr;
    }
    /*
      树的高度与节点的总数
    */
    int high() const {
      return high(_root);
    }
    int sum() const {
      return sum(_root);
    }
    /*
      递归遍历操作: 
      前中后序与当前节点的访问时机有关, 因为左孩子一定比右孩子先访问
      1. 前序遍历: VLR
      2. 中序遍历: LVR
      3. 后序遍历: LRV
      4. 层序遍历: 每一层进行一次后序遍历
    */
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
    // 后序遍历
    void postOrder_r() const {
      postOrder_r(_root);
      cout << endl;
    }
    // 层序遍历
    void levelOrder_r() const {
      int h = high();
      for (int i = 1; i <= h; ++i) {
        levelOrder_r(_root, i);
      }
      cout << endl;
    }
    /*
      非递归实现前中后序, 层序遍历
    */
    // 非递归前序遍历VLR
    // 1. 将根节点入栈
    // 2. 只要栈不为空, 出栈并处理数据, V
    // 然后将出栈的节点的右孩子和左孩子依次入栈 L R
    void preOrder() const {
      if (_root == nullptr) {
        return;
      }
      stack<Node*> s;
      s.push(_root);
      while (!s.empty()) {
        // 出栈打印数据
        Node* cur = s.top();
        s.pop();
        cout << cur->_data << " ";
        // 分别处理左子树和右子树
        // 后进先出, 先入右孩子, 再入左孩子
        if (cur->_right != nullptr) {
          s.push(cur->_right);
        }
        if (cur->_left != nullptr) {
          s.push(cur->_left);
        }
      }
      cout << endl;
    }
    // 非递归中序遍历LVR
    // 1. 从根节点作为左孩子开始, 一直将左孩子入栈 L
    // 2. 没有左孩子可以入栈, 则出栈处理数据 V
    // 3. 然后再以出栈节点的右孩子为根节点继续 R
    void inOrder() const {
      if (_root == nullptr) {
        return;
      }
      stack<Node*> s;
      Node* cur = _root;
      while (!s.empty() || cur != nullptr) {
        // 只要是当前节点不为空就入栈
        if (cur != nullptr) {
          s.push(cur);
          cur = cur->_left; // 处理左子树L
        } else {
          // 当前节点为空, L左子树处理完了
          // 出栈打印数据
          Node* node = s.top();
          s.pop();
          cout << node->_data << " ";
          // 处理右子树R
          cur = node->_right;
        }
      }
      cout << endl;
    }
    // 非递归后序遍历
    // 将LRV转换成VRL, 如果是LRV, 那么首先先处理左孩子, 将左右的左孩子入栈后,
    // 从栈中取出节点, 但是不进行处理, 继续处理右孩子, 最后再进行数据处理,
    // 这就需要将出栈的节点数据保存下来
    // 转换成VRL, 然后将数据保存在栈中, 最后输出正好是后序遍历的结果
    // 1. 将根节点入栈
    // 2. 只要栈不为空, 则从栈中取出节点进行数据处理(将数据保存在栈中)
    // 然后将出栈数据的左右节点入栈, 先入左孩子后入右孩子
    // 3. 输出数据栈中的数据
    void postOrder() const {
      if (_root == nullptr) {
        return;
      }
      stack<Node*> s1;
      stack<Node*> s2;
      s1.push(_root);
      while (!s1.empty()) {
        Node* cur = s1.top();
        s1.pop();
        s2.push(cur);
        if (cur->_left != nullptr) {
          s1.push(cur->_left);
        }
        if (cur->_right != nullptr) {
          s1.push(cur->_right);
        }
      }
      while (!s2.empty()) {
        Node* cur = s2.top();
        cout << cur->_data << " ";
        s2.pop();
      }
      cout << endl;
    }
    // 非递归的层序遍历
    // 层序遍历是一个广度优先操作, 因此非递归要配合队列来实现
    // 1. 将根节点入队
    // 2. 只要队列不为空, 则从队列中取出节点进行操作
    // 然后将出队节点的左右孩子入队
    void levelOrder() const {
      if (_root == nullptr) {
        return;
      }
      queue<Node*> q;
      q.push(_root);
      while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        cout << cur->_data << " ";
        if (cur->_left != nullptr) {
          q.push(cur->_left);
        }
        if (cur->_right != nullptr) {
          q.push(cur->_right);
        }
      }
      cout << endl;
    }
  private:
    struct Node {
      Node(const T& data) 
        : _data(data)
        , _left(nullptr)
        , _right(nullptr)
      {}
      T _data;
      Node* _left;
      Node* _right;
    };

    // 树的高度
    int high(Node* node) const {
      if (node == nullptr) {
        return 0;
      }
      // 左右子树中最大的高度+1
      int left = high(node->_left);
      int right = high(node->_right);
      return left > right ? left + 1 : right + 1;
    }
    // 节点的总数
    int sum(Node* node) const {
      if (node == nullptr) {
        return 0;
      }
      // 左右子树的节点个数+1
      int left = sum(node->_left);
      int right = sum(node->_right);
      return left + right + 1;
    }

    // 递归插入
    Node* insert_r(Node* node, const T& data) {
      if (node == nullptr) {
        // 找到了插入的位置, 返回新创建的节点
        return new Node(data);
      }
      // 如果有该数据则不插入, 返回当前节点
      if (data == node->_data) {
        return node;
      }
      // 更新地址域, 目的是为了将插入节点连接到树上
      if (_comp(data, node->_data)) { // 左子树
        node->_left = insert_r(node->_left, data);
      } else { // 右子树
        node->_right = insert_r(node->_right, data);
      }
      return node;
    }
    // 递归删除
    Node* remove_r(Node* node, const T& data) {
      // 没找到
      if (node == nullptr) {
        return nullptr;
      }
      // 找到了
      if (data == node->_data) {
        // 先判断第二种情况
        if (node->_left != nullptr && node->_right != nullptr) {
          // 找到当前节点的前驱
          Node* pre = node->_left;
          while (pre->_right != nullptr) {
            pre = pre->_right;
          }
          node->_data = pre->_data; // 覆盖当前节点
          // 删除当前节点的前驱
          node->_left = remove_r(node->_left, pre->_data);
        } else { // 第一种情况
          Node* child = node->_left;
          if (child == nullptr) {
            child = node->_right;
          }
          delete node;
          return child; // 向上回溯, 返回给父节点
        }
      }
      if (_comp(data, node->_data)) { // 左子树
        node->_left = remove_r(node->_left, data);
      } else { // 右子树
        node->_right = remove_r(node->_right, data);
      }
      return node;
    }
    // 递归查询
    Node* find_r(Node* node, const T& data) const {
      // 没找到
      if (node == nullptr) { 
        return nullptr;
      }
      // 找到了
      if (data == node->_data) {
        return node;
      }
      if (_comp(data, node->_data)) { // 左子树
        return find_r(node->_left, data);
      } else { // 右子树
        return find_r(node->_right, data);
      }
    }

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
        inOrder(node->_left);
        cout << node->_data << " ";
        inOrder(node->_right);
      }
    }
    // 后序遍历
    void postOrder_r(Node* node) const {
      if (node != nullptr) {
        postOrder_r(node->_left);
        postOrder_r(node->_right);
        cout << node->_data << " ";
      }
    }
    // 层序遍历
    void levelOrder_r(Node* node, int i) const {
      if (node == nullptr) {
        return;
      }
      // 遍历到的当前节点为第一层, 将第一层的节点值输出
      if (i == 1) { 
        cout << node->_data << " ";
      }
      // 后序遍历
      levelOrder_r(node->_left, i - 1);
      levelOrder_r(node->_right, i - 1);
    }

    Node* _root;
    Comp _comp;
};


