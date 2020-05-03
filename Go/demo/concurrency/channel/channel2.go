package main

import (
  "fmt"
  "time"
)

/*
  非阻塞通道, 非阻塞通道中设置缓冲区, 读写数据是否阻塞依赖缓冲区
  当缓冲区满时, 写数据阻塞
  当缓冲区空时, 读数据阻塞
*/

func main() {
  channel := make(chan int, 4)
  go WriteData(channel)
  ReadData(channel)
}

func ReadData(channel chan int) {
  for data := range channel {
    time.Sleep(1 * time.Second)
    fmt.Println("data:", data)
  }
}
func WriteData(channel chan int) {
  defer close(channel)
  for i := 0; i < 10; i++ {
    fmt.Println("发送",  i)
    channel <- i
  }
}
