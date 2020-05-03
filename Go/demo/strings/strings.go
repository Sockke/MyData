package main

/*
  有关字符串的一些操作
*/

import (
  "fmt"
  "strings"
)

func main() {
  str := "hello world"
  fmt.Println(str)
  // 查询字符串, 成功返回下标, 失败返回-1
  pos := strings.Index(str, "o")
  fmt.Println(pos)
  pos = strings.LastIndex(str, "o")
  fmt.Println(pos)
  // 分割字符串
  arr := strings.Split(str, " ")
  for i := 0; i < len(arr); i++ {
    fmt.Println(arr[i])
  }
  // 字符串连接
  s := []string{"sock", "is", "cool"}
  joinStr := strings.Join(s, "")
  fmt.Println(joinStr)
  joinStr = strings.Join(s, " ")
  fmt.Println(joinStr)
}
