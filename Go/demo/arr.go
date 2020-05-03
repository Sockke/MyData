package main

import "fmt"

func show(arr [4]int) {
  for i := 0; i < len(arr); i++ {
    fmt.Printf("arr[%d] = %d\n", i, arr[i])
  }
}

func main() {
  // 一维数组
  var arr = [...]int{9, 5, 2, 7}
  //for i := 0; i < len(arr); i++ {
  //  fmt.Printf("%d ", arr[i])
  //}
  //fmt.Println()

  // 二维数组
  //var arr = [][3]int {
  //  {1, 2, 3},
  //  {4, 5, 6},
  //  {7, 8, 9}, // 必须加",", 因为最后的"}"不能单独一行(也可以写成}})
  //}
  //for i := 0; i < len(arr); i++ {
  //  for j := 0; j < len(arr[i]); j++ {
  //    fmt.Printf("arr[%d][%d] = %d\n", i, j, arr[i][j])
  //  }
  //}

  show(arr)
}
