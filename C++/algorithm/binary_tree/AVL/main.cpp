#include "AVLTree.h"

int main() {
  AVLTree<int> t;
  for (int i = 1; i <= 10; ++i) {
    t.insert_r(i);
  }
  t.levelOrder_r();
  t.remove_r(9);
  t.remove_r(10);
  t.levelOrder_r();
  t.remove_r(6);
  t.levelOrder_r();
  t.remove_r(1);
  t.remove_r(2);
  t.remove_r(3);
  t.levelOrder_r();
  return 0;
}
