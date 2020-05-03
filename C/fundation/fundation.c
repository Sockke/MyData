#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  C语言中的变量的四大存储类别:
  auto register extern static
  auto:(自动存储)
    表示变量的声明周期从定义处开始, 到语句块结尾结束 
    C中的所有变量默认是auto进行存储的
  register:(寄存器存储)
    表示对变量或对象从寄存器中获取, 而不是从内存中获取
    提高变量的访问效率
    因为寄存器大小和数量有限, 因此只是建议从寄存器中获取
    如果从寄存器中获取变量, 则该变量不能取地址
  extern:(外部存储)
    表示变量可以在其他源文件中访问
    extern用于对变量和函数的声明, 表示在其他源文件中定义
  static:(静态存储)
    表示变量只能在当前源文件中访问


  sizeof:
  sizeof是操作符, 他C/C++关键字之一
  sizeof操作符在编译时期来计算类型, 变量或者对象的字节大小
  为什么sizeof计算变量或对象时可以不加(), 但是计算类型时必须加括号?
    因为sizeof int, 很容易让开发者误认为是限制或者扩展类型, 容易产生歧义 
*/

/*
  C中的一些类型:
  bool: 不要在判断语句中用bool变量与0或1进行比较, 要用true/false
  因为true/false是一个宏定义, 不同编译器对其定义的值不同, 比如说vs basic中true=-1

*/

#if 0
/*
  柔性数组, 在成员变量中定义大小为0的数组, 用来动态的为其分配内存空间
  类似于指针, 但是柔性数组本质上不属于结构体成员, 因为它不占结构体的大小
*/
typedef struct Student {
  int age;
  char name[]; // 柔性数组
}Stu;

int main() {
  printf("%lu\n", sizeof(Stu));
  const char* name = "sock";
  Stu* stu = (Stu*)malloc(sizeof(Stu) + strlen(name));
  stu->age = 18;
  strcpy(stu->name, name);
  printf("name:%s, age = %d\n", stu->name, stu->age);
  free(stu);
  return 0;
}
#endif

#if 0
/*
  逗号表达式
  (表达式1, 表达式2, ...)
  1. 从左向右依次执行逗号表达式的内容
  2. 逗号运算符的优先级最低
*/
int main() {
  int a = 0; 
  int b = (a = 2, 1, 2, 3);
  printf("a = %d\n", a);
  printf("b = %d\n", b);
  b = 5, 100;
  printf("b = %d\n", b);
  return 0;
}
#endif

int main() {
  return 0;
}
