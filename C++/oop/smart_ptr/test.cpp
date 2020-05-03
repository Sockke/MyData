// 裸指针的缺陷: 忘记释放指针指向的资源
// 1. 代码逻辑过早结束, 释放资源的代码没来得及执行
// 2. 代码中间出现异常, 释放资源的代码没来得及执行
// 3. 裸指针访问对象资源时, 无法判断对象是否存活
//
// 为什么要使用智能指针?
// 1. 防止裸指针指向的资源忘记或没来得及释放
// 2. 防止裸指针直接访问已经析构的对象
//
// 智能指针:
// 不带引用计数的智能指针:
// auto_ptr: 转移资源的所有权
// scoped_ptr: 禁止拷贝构造和拷贝赋值
// unique_ptr: 转移临时资源或局部资源的所有权
// 禁止拷贝构造和拷贝赋值, 提供带右值的构造和赋值(推荐使用unique_ptr)
// 带引用计数的智能指针: 引用计数存储在堆内存上
// shared_ptr: 多个对象指向同一个资源, 引用计数会改变, 是线程安全的
// weak_ptr: 多个对象引用同一个资源, 但是无法直接访问, 引用计数不会改变
//
// 问题:
// 1. auto_ptr能否实例化一个vector容器? vector<auto_ptr<int>>
// 不可以的, 因为vector在进行扩容时, 深拷贝会导致转移对象的所有权, 使得原先的智能指针失效
// 2. unique_ptr能否实例化一个vector容器? vector<unique_ptr<int>>
// 只能将将亡的对象用unique_ptr来接收, 因此也是不建议使用unique_ptr来实例化vector容器
// 3. shared_ptr能否大量使用?
// 不可以的, shared_ptr可能会造成循环引用(交叉引用)的问题, 一般搭配weak_ptr使用
// 4. weak_ptr如何访问资源?
// weak_ptr作为一个观察者的角色, 不能直接访问强智能指针管理的资源
// 需要进行类型提升, 类型提升可能会失败, 提升成功后作为强智能指针来访问资源
// 5. 智能指针能否定义在堆上?(智能指针的工作原理)
// 不可以的, 因为智能指针利用的是栈上的对象出作用域自动析构的特点来保证他管理的资源能够及时释放,
// 定义在堆上智能指针无法自动调用析构, 同时管理的资源也无法得到释放
//
// 总结:
// 定义时使用shared_ptr, 引用时使用weak_ptr
// 通过shared_ptr来管理创建的对象资源, 然后通过weak_ptr来引用这些资源,
// 当需要weak_ptr去访问这些资源时, 需要进行类型提升, 类型提升前先判断
// 该对象资源的引用计数, 如果为0代表资源已被释放, 类型提升失败; 如果大于0
// 代表还有强智能指针在管理这个资源, 提升成功, 引用计数加1. 
// weak_ptr提升的过程可以判断对象资源的存活状态.

#include <iostream>
#include <memory>
#include <vector>
using namespace std;
unique_ptr<int> getUniquePtr() {
  return unique_ptr<int>(new int(10));
}
int main() {
  vector< unique_ptr<int> > v;
  v.push_back(getUniquePtr());
  cout << "uptr1:" << *v[0] << endl;
  //unique_ptr<int> uptr2(new int(2));
  //v.push_back(uptr2);
  //cout << "uptr1:" << *uptr1 << endl;
  return 0;
}

#if 0
#include "shared_ptr_tmp.h"
#include <thread>
#include <chrono>

void func1() {
  // 强智能指针的交叉引用, 导致资源无法释放(互相指引, 都不放手)
  shared_ptr<A> sptra(new A());
  shared_ptr<B> sptrb(new B());
  sptra->_wptrb = sptrb;
  sptrb->_wptra = sptra;
  sptrb->func();
}
// weak_ptr提升可能会失败的情况
void func2() {
  {
    shared_ptr<A> sptra(new A());
    weak_ptr<A> wptr = sptra;
    thread thr([](weak_ptr<A> wp)->void{
        this_thread::sleep_for(chrono::seconds(2));
        shared_ptr<A> sptr = wp.lock(); 
        if (sptr != nullptr) {
        cout << sptr->sum(10, 20) << endl;
        } else {
        cout << "资源已被释放" << endl;
        }
        }, wptr);
    thr.detach();
  }
  this_thread::sleep_for(chrono::seconds(2));
}
int main() {
  //func1();
  func2();
  return 0;
}
#endif

#if 0
#include "auto_ptr.h"
#include "unique_ptr.h"
#include <functional>
using namespace std;

// 不带引用计数的智能指针
void func1() {
  AutoPtr<int> aptr(new int(10));
  AutoPtr<int> aptr2(new int(20));
  aptr = aptr2; // 转移对象所有权
  *aptr = 100;
  cout << *aptr << endl;
}

UniquePtr<int> getUniquePtr() {
  return UniquePtr<int>(new int(100));
}
void func2() {
  //UniquePtr<int> uptr(new int(10));
  //uptr = getUniquePtr();
  //UniquePtr<int> uptr(getUniquePtr());
  //cout << *uptr << endl;
  UniquePtr<int, function<void(int*)>> uptr(new int[5], [](int* uptr)->void{delete[] uptr;});
  // 通过function来保存lambda函数对象的类型
  function<int(int, int)> sum([](int a, int b)->int{return a + b;});
  cout << sum(10, 20) << endl;
}

int main() {
  func2();
  cout << "end" << endl;
  return 0;
}
#endif
