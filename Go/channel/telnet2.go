package main

import (
  "fmt"
	"io"
	"log"
	"net"
	"os"
	"time"
)

/*
  channel是goroutine之间通信的机制
  他的思想是: 不以共享数据进行通信, 而是通过通信来共享数据

  channel分为不带缓冲的channel与带缓冲的channel
  不带缓冲的channel是一个阻塞的channel, 收发数据要同步进行,
  因此简单的不带缓冲的channel可以实现两个goroutine的同步
*/

func main() {
	// 请求连接
  conn, err := net.Dial("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
		return
	}
	channel := make(chan struct{})

	go func() {
    io.Copy(os.Stdout, conn) // 忽略错误
    fmt.Println("done")
    // 睡2s再结束程序
    time.Sleep(2 * time.Second)
		channel <- struct{}{}
	}()
	func() {
		if _, err := io.Copy(conn, os.Stdin); err != nil {
			log.Fatal(err)
			return
		}
	}()
  fmt.Println("prepare")
  conn.Close()
  // channel如果没有数据, 则阻塞
	<-channel
}
