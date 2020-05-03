package main

import "fmt"

/*
  带缓冲的channel, 在底层维护了一个队列式的缓存结构
  他是非阻塞的, 在缓冲区被填满之前, 多个goroutine可以并发向里面发送数据
  当缓冲区满了之后, 会阻塞, 直到其他goroutine从里面获取数据
*/

func main() {
  channel := make(chan int, 5)
  go func() {
    for i := 0; i < 10; i++ {
      channel <- i
      fmt.Printf("%d ", i)

    }
    close(channel)
  }()
  for e := range channel {
    fmt.Printf("%d ", e)

  }
  fmt.Println()

}
