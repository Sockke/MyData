package main

import (
  "fmt"
  "time"
)

/*
  定时器
  通过定时器来定时操作某个事件

  1. 创建计时器对象
  timer := time.NewTimer(3 * time.Second)
  2. 获取通道对象
  ch_time := timer.C
  3. 取消计时器
  timer.Stop

  time.After()是第一步与第二步的结合版, 直接返回通道
  但是这样的话就无法取消定时器, 使用起来不灵活
*/

func main() {
  /*
  timer := time.NewTimer(3 * time.Second)
  ch_time := timer.C
  go func() { // 3秒钟之后被唤醒
    data := <- ch_time
    fmt.Println("finish time:", data)
  }()
  fmt.Println("start time:", time.Now())
  time.Sleep(5 * time.Second)
  */

  timer := time.NewTimer(5 * time.Second)
  ch_time := timer.C
  go func() {
    data := <- ch_time
    fmt.Println("finish time:", data)
  }()
  fmt.Println("start time", time.Now())
  time.Sleep(3 * time.Second)
  timer.Stop() // 停止计时器
}


