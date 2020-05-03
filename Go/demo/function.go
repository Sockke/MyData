package main

import "fmt"

func max(a int, b int) int {
  if a > b {
    return a
  } else {
    return b
  }
}

// 值传递, 返回2个值进行拷贝交换
//func swap(a int, b int) (int, int) {
//  return b, a
//}

// 引用传递, 通过内存地址对值直接进行改变
func swap(a *int, b *int) {
  *a, *b = *b, *a
  //tmp := *a
  //*a = *b
  //*b = tmp
}

// 匿名函数(闭包)
func getNum() func() int {
  i := 0
  return func() int {
    i++
    return i
  }
}

func main() {
  maxnum := max(3, 5)
  a, b := 1, 2
  //a, b = swap(a, b)
  swap(&a, &b)
  fmt.Println("max num =", maxnum)
  fmt.Println("a =", a, "b =", b)

  // 在闭包中获取返回变量, ret作为getNum中的匿名函数已经被保存下来
  // 下次调用ret, 直接调用闭包函数, 闭包函数具有记忆功能
  ret := getNum()
  fmt.Println("ret =", ret())
  fmt.Println("ret =", ret())
  fmt.Println("ret =", ret())
  //fmt.Println("next ret =", nextNumber())
}
