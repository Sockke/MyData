#include <stdio.h>

/*
  enum是用来定义枚举类型的数据的, 为了解决define定义枚举时的死板
  enum枚举类型的变量用来存一个整数, 因此他的大小其实是sizeof(int)

  enum与define的区别
  1. 处理时期不同, define是在预处理时进行的文本替换, 
  而enum是在编译时期确定的枚举值的大小, 并进行了文本替换(编译时期的宏)
  2. define一次只能定义一个常量, 而enum一次可以定义多个常量

  enum和define的功能几乎相同, enum存在的意义在哪?
  enum更好的管理一组有关系的常量, 有利于代码的维护
*/

enum Week{
  MONDAY,
  TUESDAT,
  WEDNESDAY,
  THURSDAY,
  FRIDAY = 10,
  SATURDAY,
  SUNDAY
}week;

int main() {
  printf("Monday = %d\n", MONDAY); // 0
  printf("Tuesday = %d\n", TUESDAT); // 1
  printf("Saturday = %d\n", SATURDAY); // 11

  printf("week size = %lu\n", sizeof(week));
  week = SUNDAY;
  printf("week = %d\n", week);
  return 0;
}
