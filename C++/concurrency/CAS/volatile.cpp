#include <iostream>
using namespace std;

// volatile的作用
// 1. 保证变量的易变性:
//  在编译时期, 将所有对该变量的操作, 都从该变量内存中去获取.
//  不能通过替换或者寄存器缓存来进行获取
// 2. 保证指令的顺序性:
//  在编译时期, 保证代码的顺序与指令的顺序是一致的

int main() {
  // 如果变量a不用volatile修饰, 那么在编译时期, 所有对变量a的操作, 
  // 都被替换为对立即数10的操作, 但是变量a所在的内存已经被修改了
  // 打印a: push 0Ah
  //
  // 如果变量a通过volatile修饰, 那么在编译时期, 所有对变量a的操作,
  // 都需要到a所在的内存中去获取.
  // 打印a: mov eax dword ptr[a]        push eax
  volatile const int a = 10;
  int* p = (int*)&a;
  *p = 20;
  cout << "a = " << a << endl;
  return 0;
}
