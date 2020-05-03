#include "BSTree.h"

int main() {
  BSTree<int> bst;
  int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 54, 78};
  for (const auto& e : arr) {
    bst.insert_r(e);
  }
  //bst.preOrder();
  bst.inOrder();
  //bst.postOrder();
  //bst.levelOrder_r();
  //bst.levelOrder();
  return 0;
}
