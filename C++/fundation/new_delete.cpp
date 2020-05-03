#include <iostream>
using namespace std;

// new和delete:
// new和malloc的区别:
// 0. malloc/free是C语言中的库函数, new/delete是C++中的运算符
// 1. malloc按字节进行开辟内存, new开辟内存时必须指定类型
// 2. malloc开辟内存不进行初始化, new开辟内存可以进行初始化
// 3. malloc开辟内存失败通过nullptr来判断, new开辟内存失败通过抛出bad_alloc异常来判断
// delete与free的区别:
// 1. free通过通过内存的起始地址来释放内存, delete释放内存之前还需要析构对象(内置类型不需要析构)

int main() {
#if 0
  // malloc开辟普通变量内存 
  int* p = (int*)malloc(sizeof(int));
  if (p == nullptr) {
    return -1;
  }
  free(p);
  // new开辟普通变量内存
  try {
    int* p1 = new int(10); // 初始化为10
    delete p1;
  } catch(bad_alloc& e) {
    cout << e.what() << endl;
  }

  // malloc开辟数组内存
  int* q = (int*)malloc(sizeof(int) * 10);
  if (q == nullptr) {
    return -1;
  }
  free(q);
  // new开辟数组内存
  int* q1 = new int[10]; // 不进行初始化
  int* q2 = new int[10](); // 初始化为int()
  delete[] q1;
  delete[] q2;
  return 0;
#endif

  // new有多少种? 4种
  // 1. 普通的new
  int* p1 = new int(10);
  delete p1;
  // 2. 不抛异常的new
  int* p2 = new (nothrow) int(10);
  if (p2 == nullptr) {
    return -1;
  }
  delete p2;
  // 3. const修饰的new
  const int* p3 = new const int(10);
  delete p3; // 在堆上开辟一段常量内存
  // 4. 定位new
  int data = 0;
  int* p4 = new (&data) int(10); // 在栈上修改某段内存
  cout << "data = " << data << endl;
  cout << "p4 = " << p4 << endl;
}
