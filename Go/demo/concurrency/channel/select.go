package main

import (
  "fmt"
  "time"
)

/*
  select 主要是监听通道的数据流动
  每个case是从通道中获取的数据, 如果都没有数据就执行defaul或者阻塞,
  如果多个通道都有数据, 那么随机选一个case执行
*/

func main() {
  ch1 := make(chan int)
  ch2 := make(chan int)

  go func() {
    time.Sleep(3 * time.Second)
    ch1 <- 100
  }()

  select {
  case <- ch1:
    fmt.Println("case1 run...")
  case <- ch2:
    fmt.Println("case2 run...")
  case <- time.After(4 * time.Second):
    fmt.Println("timeout...")
  //default:
  //  fmt.Println("default...")
  }
}

