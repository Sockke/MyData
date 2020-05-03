package main

import (
  "fmt"
  "os"
  //"io"
  "log"
)

func HandleErr(err error) {
  if err != nil {
    log.Fatal(err)
  }
}

//func ReadFile(fname string) {
//  // 1. 打开文件
//  fp, err := os.Open("./demo")
//  HandleErr(err)
//  // 关闭文件
//  defer fp.Close()
//  // 2. 读取文件
//  v := make([]byte, 1024, 1024)
//  n := 0
//  for true {
//    n, err = fp.Read(v)
//    if n == 0 || err == io.EOF {
//      break;
//    }
//    fmt.Printf(string(v[:n]))
//  }
//}

func WriteFile(fname string) {
  // 打开文件
  fp, err := os.OpenFile(fname, os.O_CREATE | os.O_WRONLY, os.ModePerm)
  HandleErr(err)
  // 关闭文件
  defer fp.Close()
  // 写文件
  v := []byte{'A', 'B', 'C', 'D'}
  n, err := fp.Write(v)
  HandleErr(err)
  fmt.Println(n)
}

func main() {
  fname := "./demo"
  WriteFile(fname)
}
