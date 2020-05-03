package main

import (
  "fmt"
  "time"
  "math/rand"
)

// 随机睡眠1 - 10秒
func RandSleep() {
  rand.Seed(time.Now().Unix())
  randNum := rand.Intn(10) + 1
  fmt.Printf("睡眠%d秒钟", randNum)
  time.Sleep(time.Duration(randNum) * time.Second)
}

func main() {
  fmt.Println("ready")
  // 睡眠3秒钟
  //time.Sleep(3 * time.Second)
  RandSleep()
  fmt.Println("start")
}
