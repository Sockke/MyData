package main

import (
  "fmt"
  "sync"
  "time"
)

/*
  通过sync.WaitGroup来实现同步的原理
  1. 先定义sync.WaitGroup这个等待组对象
  2. 通过Add来设置等待组的数量, 并通过Wait()进入等待状态
  3. 在协程结尾设置Done, 代表从等待组中移除, 直到等待组中的数量为0时, 在等待出被唤醒
*/

var mtx sync.Mutex
var wg sync.WaitGroup

var tickets int = 20

func main() {
  wg.Add(4)

  go SellTickets(1)
  go SellTickets(2)
  go SellTickets(3)
  go SellTickets(4)

  wg.Wait()
  //time.Sleep(3 * time.Second)
}

func SellTickets(name int) {
  defer wg.Done()
  for {
    mtx.Lock()
    time.Sleep(100 * time.Millisecond)
    if tickets > 0 {
      fmt.Printf("窗口%d售出第%d张票\n", name, tickets)
      tickets--
    } else {
      fmt.Printf("窗口%d的票已售空\n", name)
      mtx.Unlock()
      break
    }
    mtx.Unlock()
  }
}
