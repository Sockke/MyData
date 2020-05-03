#include "RBTree.h"

int main() {
  RBTree<int> t;
  for (int i = 1; i <= 10; ++i) {
    t.insert(i);
  }
  t.levelOrder_r();
  t.remove(9);
  t.levelOrder_r();
  t.remove(10);
  t.levelOrder_r();
  t.remove(5);
  t.levelOrder_r();
  t.remove(3);
  t.levelOrder_r();
  return 0;
}
