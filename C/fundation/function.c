#include <stdio.h>

/*
  函数的2个问题:
  
  函数指针与指针函数的区别?
  1. 函数指针本质上是指针, 函数指针可以作为函数参数成为回调函数,
  也可以接收具有相同类型的函数名, 进行函数调用
  2. 指针函数本质上是函数, 返回值为指针类型

  函数指针与函数(函数名)的区别?
  1. 函数指针本质上是指针, 函数指针可以作为函数参数成为回调函数,
  也可以用来接收相同类型的函数名, 进行函数调用
  2. 函数名虽然本质上也是指针, 但是它不是函数指针, 函数名代表这个函数的地址,
  是一个常量, 而函数指针是可以接收相同类型的任意函数的变量
*/

