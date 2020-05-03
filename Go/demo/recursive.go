package main

import "fmt"

func factorial(n int) uint64 {
  if n <= 1 {
    return 1
  }
  // 强类型
  return uint64(n) * factorial(n - 1)
}

func fibonacci(n int) int {
  if n <= 1 {
    return n
  }
  return fibonacci(n - 2) + fibonacci(n - 1)
}

func main() {
  ret := factorial(15)
  fmt.Printf("ret = %d\n", ret)
  for i := 0; i < 10; i++ {
    num := fibonacci(i)
    fmt.Printf("%d ", num)
  }
  fmt.Println()
}
