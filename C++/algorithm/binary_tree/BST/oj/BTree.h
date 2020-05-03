#include <iostream>
using namespace std;

// 二叉树
class BTree {
  public:
    BTree() : _root(nullptr) {}
    ~BTree() {}
    /*
      判断该二叉树树是否为BST
    */
    bool isBST() const {
      Node* pre = nullptr;
      return isBST(_root, pre);
    }
    /*
      判断是否为二叉树的子树
      先在二叉树中找到判断子树的根节点位置
    */
    bool isChild(BTree& bt) const {
      // 在二叉树中找子树的根节点对应的位置
      Node* cur = _root;
      while (cur != nullptr) {
        // 找到了
        if (cur->_data == bt._root->_data) {
          break;
        } else if (bt._root->_data < cur->_data) {
          cur = cur->_left;
        } else {
          cur = cur->_right;
        }
      }
      // 没找到
      if (cur == nullptr) {
        return false;
      }
      return isChild(cur, bt._root);
    }

    /*
      求一个二叉树的镜像翻转
    */
    void mirrorFlip() {
      mirrorFlip(_root);
    }

    /*
      判断一个二叉树是否是镜像对称
    */
    bool isSymmetry() const {
      if (_root == nullptr) {
        return true;
      }
      return isSymmetry(_root->_left, _root->_right);
    }

    /*
      给定二叉树的前序遍历与中序遍历, 来构建这个二叉树
    */
    void rebuild(int* pre, int* mid, int n) {
      _root = rebuild(pre, 0, n - 1, mid, 0, n - 1);
    }

    /*
      求树的高度
    */
    int high() const {
      return high(_root);
    }
    /*
      判断该二叉树是否是平衡树
      平衡树是指左右子树的高度差不能超过1
    */
    bool isBalance() const {
      //return isBalance(_root);
      bool flag = true;
      isBalance(_root, 1, flag);
      return flag;
    }

    /*
      求二叉树中序遍历倒数第k个元素
    */
    int getKOfVal(int k) {
      Node* k_node = getKOfVal(_root, k);
      if (k_node != nullptr) {
        return k_node->_data;
      } else {
        throw "no k of value";
      }
    }

  public:
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

    // 判断该二叉树是否为BST
    // 根据BST中序遍历为升序的特性来判断
    // 每次都判断当前节点的值是否大于前驱节点的值
    bool isBST(Node* node, Node*& pre) const {
      if (node == nullptr) {
        return true;
      }
      if (!isBST(node->_left, pre)) {
        return false;
      }
      // 如果当前的值小于前驱节点的值, 那么就不是BST
      if (pre != nullptr)  {
        if (node->_data < pre->_data) {
          return false;
        }
      }
      pre = node;
      return isBST(node->_right, pre);
    }

    // 判断是否是该二叉树中的子树问题
    // 给定2个二叉树, 判断二叉树2是否是二叉树1的子树
    bool isChild(Node* node, Node* child) const {
      // 两边正好都相同 
      if (node == nullptr && child == nullptr) {
        return true;
      }
      // 二叉树包含子树
      if (node != nullptr && child == nullptr) {
        return true;
      }
      // 二叉树不包含该子树
      if (node == nullptr && child != nullptr) {
        return false;
      }
      if (node->_data != child->_data) {
        return false;
      }
      return isChild(node->_left, child->_left) && isChild(node->_right, child->_right);
    }

    // 求一个二叉树的镜像翻转
    // 镜像翻转就是和照镜子一样, 翻转成镜子中的自己
    // 其实就是前序遍历到每个节点时, 交换左右孩子节点的地址
    void mirrorFlip(Node* node) {
      if (node == nullptr) {
        return ;
      }
      // 交换该节点左右孩子的地址
      Node* tmp = node->_left;
      node->_left = node->_right;
      node->_right = tmp;
      mirrorFlip(node->_left);
      mirrorFlip(node->_right);
    }

    // 判断二叉树是否是镜像对称
    bool isSymmetry(Node* left, Node* right) const {
      // 左右刚好对称
      if (left == nullptr && right == nullptr) {
        return true;
      }
      // 左右不对称
      if (left == nullptr || right == nullptr) {
        return false;
      }
      // 如果还判断数据的话
      if (left->_data != right->_data) {
        return false;
      }
      return isSymmetry(left->_left, right->_right)
        && isSymmetry(left->_right, right->_left);
    }

    // 给定二叉树的前序遍历与中序遍历, 来构建这个二叉树
    Node* rebuild(int* pre, int i, int j, int* mid, int m, int n) {
      if (i > j || m > n) {
        return nullptr;
      }
      // 根据当前前序, 创建当前位置的根节点
      Node* node= new Node(pre[i]);
      // 根据当前中序, 找到根节点的位置, 从而确定左右子树的范围 
      for (int k = m; k <= n; ++k) {
        if (mid[k] == pre[i]) {
          // 画图, 前序确定根节点, 中序确定左右子树范围
          node->_left = rebuild(pre, i + 1, i + (k - m), mid, m, k - 1);
          node->_right = rebuild(pre, i + (k - m) + 1, j, mid, k + 1, n);
          return node;
        }
      }
      return node;
    }

    // 求树的高度
    int high(Node* node) const {
      if (node == nullptr) {
        return 0;
      }
      int left = high(node->_left);
      int right = high(node->_right);
      return left > right ? left + 1 : right + 1;
    }
    // 判断该二叉树是否是平衡树
    // 通过后序遍历的思想, 从下向上回溯, 
    // 判断左右子树的高度差
    bool isBalance(Node* node) const {
      if (node == nullptr) {
        return true;
      }
      if (!isBalance(node->_left)) {
        return false;
      }
      if (!isBalance(node->_right)) {
        return false;
      }
      int left = high(node->_left);
      int right = high(node->_right);
      return abs(left - right) <= 1;
    }
    // 判断二叉树是否是平衡树
    // 通过返回树的高度, 用参数来记录该二叉树是否是平衡树
    // 在性能上要比上边每个节点都要递归求高度要高
    int isBalance(Node* node, int height, bool& flag) const {
      if (node == nullptr) {
        return height;
      }
      // 左子树的高度
      int left = isBalance(node->_left, height + 1, flag);
      // 右子树的高度
      int right = isBalance(node->_right, height + 1, flag);
      // 只要有一个节点的高度差大于 1, 那么就不是平衡树
      if (abs(left - right) > 1) {
        flag = false; 
      }
      // 返回树的高度, 左右子树高度的最大值
      return max(left, right);
    }

    // 在二叉树中找中序遍历的倒数第k个节点
    // 1.中序遍历LVR的倒数第k个节点, 其实就是RVL的第k个节点
    // 先遍历右子树后遍历左子树, 找到第k个节点即可
    // 2. 也可以先求出树的节点数量, 但是这样需要遍历2次二叉树, 性能较低
    Node* getKOfVal(Node* node, int& k) {
      // 没找到
      if (node == nullptr) {
        return nullptr;
      }
      // 向右子树中找, 如果找到直接返回节点
      Node* cur = getKOfVal(node->_right, k);
      if (cur != nullptr) {
        return cur;
      }
      // 找到了
      if (k-- == 1) {
        return node;
      }
      // 向左子树中找
      return getKOfVal(node->_left, k);
    }

    Node* _root;
};
