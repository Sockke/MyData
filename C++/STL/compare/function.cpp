#include <iostream>
#include <functional>
#include <string>
#include <map>

using std::cout;
using std::endl;

// function: 函数对象
// 1. 通过function可以保留任何的函数类型, 包装成函数对象

void showAllBooks() {cout << "展示所有图书" << endl;}
void doBorrow() {cout << "借书" << endl;}
void doReturn() {cout << "还书" << endl;}
void doQuery() {cout << "查询书籍" << endl;}
void loginout() {cout << "注销" << endl;}
int main() {
  // C语言中可以通过函数指针数组来实现转移表
  //typedef void(*T)();
  //T menu[] = {
  //  showAllBooks, 
  //  doBorrow,
  //  doReturn,
  //  doQuery,
  //  loginout
  //};
  // C++可以通过map+function来实现转移表
  std::map<int, std::function<void()>> menu;
  menu.insert({1, showAllBooks});
  menu.insert({2, doBorrow});
  menu.insert({3, doReturn});
  menu.insert({4, doQuery});
  menu.insert({5, loginout});
  while (1) {
    cout << "1. 展示所有图书" << endl;
    cout << "2. 借书" << endl;
    cout << "3. 还书" << endl;
    cout << "4. 查询书籍" << endl;
    cout << "5. 注销" << endl;
    int choice = 0;
    std::cin >> choice;
    //if (choice < 1 || choice > 5) {
    //  cout << "输入有误" << endl;
    //} else {
    //  menu[choice - 1]();
    //}
    auto it = menu.find(choice);
    if (it == menu.end()) {
      cout << "输入有误..." << endl;
    } else {
      it->second();
    }
  }
  return 0;
}

#if 0
void show() {
  cout << "hello world" << endl;
}
void showStr(const std::string& str) {
  cout << str << endl;
}
int sum(int left, int right) {
  return left + right;
}

class Test {
  public:
    void show(const std::string& str) {
      cout << str << endl;
    }
    static void showInfo(const std::string& str) {
      cout << str << endl;
    }
};

int main() {
  // 保留普通函数的类型
  std::function<void()> func1 = show;
  func1();
  std::function<void(const std::string&)> func2 = showStr;
  func2("sock");
  std::function<int(int, int)> func3 = sum;
  cout << func3(100, 200) << endl;
  
  // 保留成员函数的类型, 需要依赖对象
  Test t;
  std::function<void(Test*, const std::string&)> func4 = &Test::show;
  func4(&t, "hehe");
  // 保留静态成员函数的类型
  std::function<void(const std::string&)> func5 = Test::showInfo;
  func5("haha");
  return 0;
}
#endif
