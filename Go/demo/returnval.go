package main

import "fmt"

// 变量的声明: var ret type = value
// var a int = 1

/*
  全局变量的声明
  var (
    a int 
    b bool
    c string
  )
*/

func main() {
  _, b, c := numbers()
  fmt.Println(b, c)
}

func numbers() (int, bool, string) {
  /*
    局部变量的声明 
    a := 1
    b := false
    c, d := true, "sock"
  */
  a, b, c := 1, false, "sock"
  return a, b, c
}

// 常量的声明与定义
// const a int
// const a int = 1 // 显示定义
// const a = 1 // 隐式定义

// 数组的声明与定义
// var arr [6]int
// var arr = [...]int{9, 5, 3, 7}

// 结构体的声明与定义
// var p Person
// var p = Person{"sock", 19, 1, "5631076"}

