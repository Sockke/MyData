#include "hungry.h"
using namespace std;

int main() {
  Singleton* s1 = Singleton::getInstance(); 
  Singleton* s2 = Singleton::getInstance();
  cout << "s1 = " << s1 << endl;
  cout << "s2 = " << s2 << endl;
  return 0;
}

#if 0
#include "lazy.h"
using namespace std;

int main() {
  Singleton* s1 = Singleton::getInstance();
  Singleton* s2 = Singleton::getInstance();
  cout << "s1 = " << s1 << endl;
  cout << "s2 = " << s2 << endl;
  return 0;
}
#endif

// 饿汉模式: 在程序运行之前, 就生成了唯一的实例
// 懒汉模式: 在程序执行到第一次获取实例的代码时, 才生成唯一的实例
//
// 因为饿汉模式是在编译时期就产生了唯一的实例, 因此不存在所谓的线程安全问题
// 懒汉模式多个线程可能同时获取唯一实例, 会存在线程安全的问题,
// 可以考虑通过mutex+double check来保证原子操作, 同时还要考虑缓存问题, 对实例用volatile修饰
// 或者通过static局部变量来避免线程安全, 因为static局部变量在汇编层面保证了线程的安全
