package main

import (
  "fmt"
  "sync"
  "time"
)

/*
  go中的sync.RWMutex实现了读写锁的功能
  读写锁适用于多读少写的场景, 因为本身读数据不存在竞争条件, 因此不需要互斥,
  读写锁的读锁是可以获取多次的, 所读数据是共享的, 这样相比于互斥锁, 效率要更高一些

  读的时候, 其他协程只能读, 不能写
  写的时候, 其他协程既不能读, 也不能写
*/

var wg sync.WaitGroup
var mtx sync.RWMutex

func main() {
  wg.Add(4)
  go WriteData(1)
  go ReadData(2)
  go ReadData(3)
  go WriteData(4)
  wg.Wait()
}

func WriteData(index int) {
  defer wg.Done()
  mtx.Lock() // 设置写锁
  fmt.Println(index, "start write")
  fmt.Println(index, "writting")
  time.Sleep(2 * time.Second)
  fmt.Println(index, "finish write")
  mtx.Unlock() // 解锁
}

func ReadData(index int) {
  defer wg.Done()
  mtx.RLock() // 设置读锁
  fmt.Println(index, "start read...")
  fmt.Println(index, "reading")
  time.Sleep(2 * time.Second)
  fmt.Println(index, "finish read...")
  mtx.RUnlock() // 解锁
}
