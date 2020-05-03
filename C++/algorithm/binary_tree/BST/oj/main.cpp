#include "BSTree.h"
#include "BTree.h"

void test() { 
  int arr2[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 54, 78};   
  BSTree bst;
  for (const auto& e : arr2) {
    bst.insert(e);
  }
  //bst.preOrder_r();
  //bst.inOrder_r();
  //cout << bst.high() << endl;
  bst.inOrder_r();
}

void test1() {
  using Node = BTree::Node;
  BTree bt; 
  bt._root = new Node(40);
  Node* node1 = new Node(20);
  Node* node2 = new Node(20);
  bt._root->_left = node1;
  bt._root->_right = node2;
  Node* node3 = new Node(30);
  node1->_right = node3;
  cout << bt.isSymmetry() << endl;
}

void test2() {
  using Node = BTree::Node;
  BTree t1;
}

int main() {
  test();
  return 0;
}
