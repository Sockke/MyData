package main

import "fmt"

// range类似于C++中的范围for
// for i, e:= range container {
//   i为下标, e为元素
//   i为key, e为value
// }

// 请切片的和
func getSum(v []int) int {
  sum := 0
  for _, e := range v {
    sum += e
  }
  return sum
}

// 找切片中值为2的下标
func getIndex(v []int) int {
  for i, e := range v {
    if e == 2 {
      return i
    }
  }
  return -1
}

func main() {
  // 定义一个切片
  v := []int{9, 5, 1, 7}
  //sum := getSum(v)
  //fmt.Println("sum =", sum)
  index := getIndex(v)
  fmt.Println("index =", index)
}
