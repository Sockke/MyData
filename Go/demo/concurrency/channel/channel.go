package main

import (
  "fmt"
  "time"
)

/*
  通道: 不以共享数据进行通信, 而是通过通信来共享数据
  通道可以连接多个协程进行通信, 协程可以向通道中读写数据,
  通道本身保证了安全性, 同时阻塞通道保证了同步

  阻塞通道: 一读一写
  1. 创建通道: 
  channel := make(chan int)
  2. 向通道中写数据: 
  channel <- data
  3. 在通道中读数据
  data := <- channel
  4. 关闭通道
  close(channel)
*/

func main() {
  channel := make(chan int)
  //go WriteData(channel)
  //ReadData(channel)
  //fmt.Println("main over...")
}

//func ReadData(channel chan int) {
//  for {
//    time.Sleep(1 * time.Second)
//    data, ok := <- channel // 获取ok值来判断通道是否关闭
//    if !ok {
//      break
//    }
//    fmt.Println(data)
//  }
//}
func ReadData(channel chan int) {
  // range来遍历通道时, 会判断通道是否关闭, 如果关闭则结束遍历
  for data := range channel {
    time.Sleep(1 * time.Second)
    fmt.Println(data)
  }
}
func WriteData(channel chan int) {
  for i := 0; i < 10; i++ {
    fmt.Println("写入", i)
    channel <- i
  }
  close(channel) // 关闭通道告知接收方, 不再发送数据了
}

/*
func main() {
  channel := make(chan int)

  go func() {
    fmt.Println("正在等待数据")
    data := <- channel
    fmt.Println("data:", data)
  }()

  time.Sleep(3 * time.Second)
  data := 10
  channel <- data
  time.Sleep(3 * time.Second)
}
*/
