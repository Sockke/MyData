package main

import (
  "fmt"
  "time"
)

func main() {
  t1 := time.Now()
  fmt.Println("t1:", t1)
  // 时间的加减
  t2 := t1.Add(5 * time.Minute) // 加上5分钟
  fmt.Println("t2:", t2)
  t3 := t1.Sub(t2) // t1与t2间隔多长时间
  fmt.Println("t3:", t3)
  t4 := t1.AddDate(1, 0, 0) // 加1年
  fmt.Println("t4:", t4)
}
