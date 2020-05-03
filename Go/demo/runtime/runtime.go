package main

import (
  "fmt"
  "time"
  "runtime"
)

/*
  go + 函数: 启动协程
  runtime.Gosched(): 出让CPU
  runtime.Goexit(): 终止协程
*/

func main() {
  // 获取GOROOT路径
  //goRoot := runtime.GOROOT()
  //fmt.Println("GOROOT:", goRoot)

  // 获取逻辑CPU的数量
  //cpuNum := runtime.NumCPU()
  //fmt.Println("CPU num:", cpuNum)

  //go func() {
  //  for i := 0; i < 5; i++ {
  //    runtime.Gosched()
  //    fmt.Println("index:", i)
  //  }
  //}()
  //go func() {
  //  fmt.Println("start...")
  //  fmt.Println("end...")
  //}()

  go func() {
    fmt.Println("start...")
    fun()
    fmt.Println("end...")
  }()
  time.Sleep(3 * time.Second)
}

func fun() {
  for i := 0; i < 5; i++ {
    if i == 2 {
      runtime.Goexit()
    }
    fmt.Println("index:", i)
  }
}
