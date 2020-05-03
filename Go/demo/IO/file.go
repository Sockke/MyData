package main

import (
  "fmt"
  "os"
)

func main() {
  // 创建文件 --- fp, err := os.Create(path)
  //fp, err := os.Create("./demo")
  //if err != nil {
  //  fmt.Println(err)
  //  return
  //}
  //fmt.Println(fp)

  // 打开文件 --- fp, err := os.OpenFile(path, way, mode)
  //fp, err := os.OpenFile("./demo", os.O_RDONLY, os.ModePerm)
  //if err != nil {
  //  fmt.Println(err)
  //  return
  //}
  //fmt.Println(fp)

  // 打开文件
  fp, err := os.Open("./demo")
  if err != nil {
    fmt.Println("err:", err)
    return
  }
  fmt.Println(fp)
}
