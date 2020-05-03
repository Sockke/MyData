#include <iostream>
#include <string>
using namespace std;

class BTree {
  public:
    BTree(char* s) : root(nullptr) {
      root = build(s);
    }

    struct TreeNode;
    TreeNode* build(char* s) {
      if (s[index] == '\0') {
        return nullptr;
      } else if (s[index] == '#') {
        return nullptr;
      } else {
        TreeNode* node = new TreeNode(s[index]);
        ++index;
        node->_left = build(s);
        ++index;
        node->_right = build(s);
        return node;
      }
    }

    void preOrder() {
      preOrder(root);
    }

    struct TreeNode {
      TreeNode(char val)
        : _val(val)
        , _left(nullptr)
        , _right(nullptr)
      {}
      char _val;
      TreeNode* _left;
      TreeNode* _right;
    };

    string getString() const {
      return s;
    }

  private:
    void preOrder(TreeNode* node) {
      if (node != nullptr) {
        s += (string(1, node->_val) + ",");
        preOrder(node->_left);
        preOrder(node->_right);
      } else {
        s += "#,";
      }
    }

    TreeNode* root;

    string s;
    static int index;
};
int BTree::index = 0;

int main() {
  char s[] = "abc##de#g##f###";
  BTree t(s);
  t.preOrder();
  cout << t.getString() << endl;
  return 0;
}

