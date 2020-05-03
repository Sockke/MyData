package main

import "fmt"

// iota 特殊常量, 可以被系统自动更改的常量, 一般用于枚举
// const定义变量, 没增加一行, iota++
// 枚举
const (
  a = 1 << iota // 1<<0
  b = 3 << iota // 3<<(0+1)
  // 只写声明, 默认是上一行的表达式
  c // 3<<(1+1)    
  d // 3<<(2+1)
)

func main() {
  fmt.Println("a:", a)
  fmt.Println("b:", b)
  fmt.Println("c:", c)
  fmt.Println("d:", d)
}

/*
import (
  "fmt"
  "unsafe"
)

const (
  STR = "sock"
  LEN = len(STR)
  SIZE = unsafe.Sizeof(STR)
)

func main() {
  //const LENGTH int = 10 // 显示定义常量
  //const WIDTH = 20 // 隐式定义常量
  //area := LENGTH * WIDTH
  //fmt.Println("area:", area)

  //const LENGTH, WIDTH = 10, 20
  //area := LENGTH * WIDTH
  //fmt.Println("area:", area)

  fmt.Println("STR:" + STR, "LEN:", LEN, "SIZE:", SIZE)
}
*/
