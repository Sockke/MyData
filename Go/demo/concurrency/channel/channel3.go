package main

import (
  "fmt"
)

/*
  定向通道, 一般用作参数来限制对通道的操作权限, 即只读或者只写
*/

func main() {
  channel := make(chan string)
  go WriteData(channel)
  data := ReadData(channel)
  fmt.Println("data:", data)
}

func WriteData(channel chan <- string) {
  data := "sock"
  channel <- data
  fmt.Println("WriteData func over...")
}

func ReadData(channel <- chan string) string {
  data := <- channel
  return data
}
