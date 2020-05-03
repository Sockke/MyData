package main

import "fmt"

// go中切片, 类似于C++中vector

func show(v []int) {
  fmt.Printf("len=%d, cap=%d, v = %v\n", len(v), cap(v), v)
}

//func show2(v []int) {
//  for i := 0; i < len(v); i++ {
//    fmt.Printf("v[%d] = %d ", i, v[i])
//  }
//  fmt.Println()
//}

func main() {
  v := []int{0, 1, 2, 3, 4, 5, 6}
  fmt.Printf("[1:3] = %v\n", v[1:3]) // 打印[1, 3) -- 1, 2
  fmt.Printf("[:3] = %v\n", v[:3]) // 打印[0, 3) -- 0, 1, 2
  fmt.Printf("[3:] = %v\n", v[3:]) // 打印[3, 7) -- 3, 4, 5, 6
  show(v)
  var v1 []int
  // 类似于C++中vector的push_back
  v1 = append(v1, 9)
  v1 = append(v1, 5)
  v1 = append(v1, 2)
  v1 = append(v1, 7)
  show(v1)
  // 拷贝
  var v2 = make([]int, 3, 4)
  copy(v2, v1)
  show(v2)
}

/*
func main() {
  // 声明一个空的切片
  var v1 []int
  show(v1)
  // 声明一个有长度和容量的切片
  var v2 = make([]int, 2, 5) // 长度为2, 容量为5, 默认初始化
  show(v2)
  // 定义一个切片
  v3 := []int{0, 1, 2, 3, 4, 5, 6}
  show(v3)
  show2(v3)
}
*/
