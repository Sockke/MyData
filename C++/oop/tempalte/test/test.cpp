//#include "Vector.h"
#include "last_vector.h"
using namespace std;

// 空间配置器
// 原理: 将new和delete实现的操作分离
// 空间配置器分别实现了内存开辟, 构造对象, 析构对象, 内存释放的功能
//
// 为什么使用空间配置器:
// 1. 因为当自定义类型作为模板参数类型时, 如果构造函数中直接通过new来操作,
// 不仅实现了内存开辟, 同时调用了元素对象的构造函数, 这不符合我们的逻辑.
// 2. 当移除对象或者析构对象时, 如果直接通过delete来操作,
// 不仅调用了元素的析构函数, 同时也对当前指针指向的内存进行释放, 这也不符合我们的逻辑
// 3. 我们希望定义容器对象时, 只开辟内存, 当向容器中添加元素对象时, 才构造元素对象;
// 当移除元素对象时, 只析构元素对象; 当销毁对象时, 先将容器中有效的元素对象析构之后, 
// 再释放这段内存. 
// 因此我们必须要将内存开辟, 构造对象, 析构对象, 内存释放的操作进行分离

class Tmp {
  public:
    Tmp() {
      cout << "Tmp()" << endl;
    }
    Tmp(const Tmp& t) {
      cout << "Tmp(const Tmp&)" << endl;
    }
    Tmp& operator=(const Tmp& t) {
      cout << "operator=(const Tmp&)" << endl;
      return *this;
    }
    ~Tmp() {
      cout << "~Tmp()" << endl;
    }
};

int main() {
  Tmp t1, t2;
  cout << "------------" << endl;
  Vector<Tmp> vec;
  cout << "------------" << endl;
  vec.push_back(t1);
  cout << "------------" << endl;
  return 0;
}

#if 0
int main() {
  Vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(rand() % 100);
  }
  while (!v.empty()) {
    cout << v.back() << " ";
    v.pop_back();
  }
  cout << endl;
  return 0;
}
#endif
