#include <iostream>
#include <string>
using namespace std;

// 抽象类:
// 包含纯虚函数的类叫做抽象类.
// 抽象类不能实例化对象, 普通类可以.
// 派生类通过重写抽象基类的纯虚函数之后, 才能进行实例化
// 对于不需要实例化的, 但是需要使用该类指针来指向派生类的类, 建议定义成抽象类
//
// 多态:
// 什么是多态?
// 静态多态: 函数重载, 模板
// 动态多态:
//   基类的指针或引用指向不同派生类的对象, 通过调用同名覆盖方法, 来完成不同功能
// 如何实现多态?
// 多态是基于函数的动态绑定来实现的, 
// 基类中必须含有虚函数来使得基类的指针可以动态的指向不同派生类对象的虚函数表
// 多态的好处?
// 1. 从功能上来讲, 基类的指针或引用来接收不同的派生类对象,
// 通过调用指定的覆盖方法来实现不同的功能
// 2. 从设计上来讲, 使用多态可以使得一套接口能够处理所有的派生类对象.
// 这遵循了软件设计的"开闭原则", 即扩展开放, 修改关闭.
// 保证了接口的可扩展性, 和接口的安全性

class Animal {
  public:
    Animal(const string& name) : _name(name) {}
    virtual void bark() = 0;
  protected:
    string _name;
};

class Dog : public Animal {
  public:
    Dog(const string& name) : Animal(name) {}
    void bark() {
      cout << "Dog:" << "wangwang" << endl;
    }
};
class Cat : public Animal {
  public:
    Cat(const string& name) : Animal(name) {}
    void bark() {
      cout << "Cat:" << "miaomiao" << endl;
    }
};
class Pig : public Animal {
  public:
    Pig(const string& name) : Animal(name) {}
    void bark() {
      cout << "Pig:" << "hengheng" << endl;
    }
};

void Bark(Animal* animal) {
  animal->bark();
}

int main() {
  Dog dog("德牧");
  Cat cat("蓝猫");
  Pig pig("佩奇");
  Bark(&dog);
  Bark(&cat);
  Bark(&pig);
  return 0;
}
