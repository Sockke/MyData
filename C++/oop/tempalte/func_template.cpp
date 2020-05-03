#include "func_template.h"
#include <iostream>
using namespace std;

// 函数模板: 本质上是模板, 不参与编译, 因为类型不确定
// 函数模板的实例化: 编译时期, 函数模板特化或在函数调用点进行实例化
// 1. 根据用户指定的模板类型, 显示构造模板函数
// 2. 根据用户传入的参数类型, 隐式推导模板函数
// 模板函数: 函数模板实例化后产生模板函数, 本质上是函数, 进行编译产生符号
//
// 模板特化: 不由编译器构造模板函数, 而是由用户自定义构造模板函数
// 来实现对特殊类型参数的特殊实例化
//
// 模板函数与普通函数的区别?
// 1. 模板函数是通过函数模板实例化而来的, 普通函数直接由用户定义而来的
// 2. 模板函数的名字是有函数模板名字+函数模板参数构成的, 
// 因此模板函数与普通函数是不构成重载的
// 3. 当函数模板名与普通函数名相同时, 函数调用优先调用普通函数, 除非指定模板参数,
// 才进行实例化出模板函数进行调用
//
// 函数模板一般定义在头文件中
// 1. 当源文件使用到函数模板时, 直接将头文件包含进来即可
// 2. 函数模板不放在源文件的原因, 因为函数模板不参与编译, 因此当其他源文件
// 使用该模板时, 会出现链接错误; 必须在当前源文件中实例化函数模板, 在其他源文件中声明模板函数
// 实例化函数模板: template bool myCompare<int>(int, int);

#if 0
int main() {
  myCompare(1, 2);
  myCompare(1.1, 2.2);
  myCompare("hello", "world");
  myCompare<double>(1, 2.2);
  return 0;
}
#endif

//template<class T>
//bool myCompare(T a, T b);

template bool myCompare(int, int);

int main() {
  bool ret = myCompare(1, 2);
  cout << ret << endl;
}

#if 0
// 非模板类型参数:
// 1. 必须是int家族的类型
// 2. 必须是常量, 比如说const int size = 1, const int size = sizeof(arr) / sizeof(arr[0])
// 3. 非模板类型参数不能修改, 在编译时期直接进行常量的替换
template<class T = int, int SIZE>
void bubble_sort(T* arr) {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

int main() {
  int arr[] = {9, 5, 2, 7};
  const int size = sizeof(arr) / sizeof(arr[0]); 
  bubble_sort<int, size>(arr);
  for (const auto& e : arr) {
    cout << e << " ";
  }
  cout << endl;
  return 0;
}
#endif
