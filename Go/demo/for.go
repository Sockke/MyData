package main

import "fmt"

func main() {
  // 类似于C中的for循环
  sum := 0
  for i := 0; i < 10; i++ {
    sum += i
  }
  fmt.Println("sum =", sum)

  // 类似于C中的while循环
  sum = 0
  i := 9
  for i >= 0 {
    sum += i
    i--
  }
  fmt.Println("sum =", sum)
}
