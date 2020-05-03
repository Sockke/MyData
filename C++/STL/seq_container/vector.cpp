#include <iostream>
#include <vector>
using namespace std;

// vector与deque的区别:
// 1. 底层结构不同. vector的底层是一个动态的一维数组, 内存是完全连续的;
// deque底层是一个动态的二维数组, 一维连续, 二维内存彼此之间不连续, 因此是分段连续的
// 因此deque对内存的利用效率更高
// 2. 接口的效率不同. vector没有提供push_front和pop_front, 因为vector的头部的插入和删除
// 都是O(n), deque是双端队列, 两端的插入和删除都是O(1)
// 3. 扩容的效率不同. vector的内存是完全连续的, 扩容引起元素的移动相比于deque来说效率
// 更高一些. 因为deque二维空间彼此是不连续, 元素的移动可能会跨越不同内存段, 效率相对来说较低一些.
// 随机访问的效率也是同样的道理.
//
// vector与list的区别:
// 1. 底层结构不同. vector的底层是一个动态的一维数组, 内存是完全连续的.
// list底层是一个双向循环链表, 内存是不连续的.
// 2. 接口的效率不同. vector没有提供push_front和pop_front, 因为他对头插和头删复杂度为O(n),
// 只能通过insert, erase来在头部或中间进行操作. 
// list对两端的插入或删除操作都是O(1), 并且在中间进行insert, erase同样是O(1).
// 3. 扩容的效率不同. vector在进行添加元素的时候可能会引起扩容, 扩容操作首先先额外开辟
// 一段更大的空间, 然后将原来空间的元素全部拷贝到新空间, 然后再释放原来的空间, 扩容的开销
// 是比较大的. 
// list是链式结构, 不需要进行这种扩容操作, 因此list相对稳定一些
// 4. 随机访问的支持. vector内存是完全连续的, 支持随机访问, 时间复杂度为O(1);
// list是链式结构, 不支持随机访问, 必须通过遍历来访问指定的元素, 时间复杂度为O(n)

// 顺序容器的使用场景:
// 1. 随机访问的操作比较多, 但是添加或删除元素的操作较少, 可以考虑vector或者deque
// 2. 添加或删除的操作比较多, 但是随机访问操作少, 可以考虑list
int main() {
  vector<int> v;
  cout << v.capacity() << endl; //0
  v.push_back(1); 
  cout << v.capacity() << endl; //1
  v.push_back(2);
  cout << v.capacity() << endl; //2
  v.push_back(2);
  cout << v.capacity() << endl; //4
  v.push_back(3);
  v.push_back(4);
  cout << v.capacity() << endl; //4

  return 0;
}
