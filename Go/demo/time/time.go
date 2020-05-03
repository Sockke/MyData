package main

import (
  "fmt"
  "time"
)

// 时间格式字符串为: "2006年1月2日 15点4时5分"
// "2006-01-02 15:04:05"
// "2006/01/02"

// time.Time->string
func GetTime() string {
  t1 := time.Now()
  return t1.Format("2006-01-02 15:04:05")
}

// string->time.Time
func GetTimeObj(t string) (time.Time, error) {
  t1, err := time.Parse("2006-01-02 15:04:05", t)
  return t1, err
}

// 获取年月日, time.Month是一个枚举类型
func GetDate(t time.Time) (int, time.Month, int) {
  year, month, day := t.Date()
  return year, month, day
}
// 获取时分秒
func GetClock(t time.Time) (int, int, int) {
  hour, minute, second := t.Clock()
  return hour, minute, second
}

func GetTimestamp(t time.Time) int64 {
  return t.Unix()
}

func main() {
  t1 := GetTime()
  fmt.Println("Date:", t1)
  t2, err := GetTimeObj(t1)
  if err != nil {
    fmt.Println("format error")
    return
  }
  fmt.Println("Date:", t2)
  fmt.Printf("%T\n", t2)
  fmt.Println("--------------------------")
  // 获取年月日
  year, month, day := GetDate(t2)
  fmt.Printf("year:%d, month=%s, day=%d\n", year, month, day)
  // 获取时分秒
  hour, minute, second := GetClock(t2)
  fmt.Printf("hour:%d, minute=%d, second=%d\n", hour, minute, second)
  fmt.Println("--------------------------")
  // 单独获取 年, 月, 日
  y := t2.Year()
  fmt.Println("y:", y)
  m := t2.Month()
  fmt.Println("m:", m)
  d := t2.Day()
  fmt.Println("d:", d)
  fmt.Println("--------------------------")
  // 获取时间戳 
  timestamp := GetTimestamp(t2)
  fmt.Println("timestamp:", timestamp)
}
