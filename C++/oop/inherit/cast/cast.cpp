#include <iostream>
using namespace std;

/*
  C++的四种类型转换函数:
  1. static_cast
  静态转换, 在编译时期就可以确定的类型转换, 一般用于相关类型的转换(比如说char->int)
  不能用于运行时的类型检查, 存在安全隐患, 比如说在向下转型时(父->子), 调用子类的同名覆盖方法会引起段错误
  static_cast与reinterpret_cast搭配可以完成类似C中的强转
  static_cast用于相关类型的强转, reinterpret_cast可以用于不相关类型的指针强转
  2. dynamic_cast
  动态转换, 在运行时期才能确定的类型转换, 一般用于多态中, 父类向子类的转换
  (当父类的指针指向子类对象时, 向下转换会成功, 否则会失败, 失败返回nullptr)
  因此dynamic_cast可以判断父类指针是否指向该子类对象
  3. const_cast
  去掉对象的const属性, 比如说(const int->int)
*/

class Person {
  public:
    virtual void show() {cout << "Person" << endl;}
};
class Student : public Person {
  public:
    void show() {cout << "Student" << endl;}
    void print() {cout << "sock" << endl;}
};
class Teacher: public Person {
  public:
    void show() {cout << "Teacher" << endl;}
    void print() {cout << "shilei" << endl;}
};

int main() {
  volatile const int a = 10;
  int* p = const_cast<int*>(&a);
  *p = 20;
  cout << *p << endl;
  cout << a << endl;
  return 0;
}
