package main

import "fmt"

func createName(m map[int]string) {
  m[0] = "sock"
  m[3] = "laoma"
  m[6] = "liuwei"
  m[4] = "liuchen"
}

func show(m map[int]string) {
  //for key := range m {
  //  fmt.Printf("%d: %s\n", key, m[key])
  //}
  for key, val := range m {
    fmt.Printf("%d: %s\n", key, val)
  }
}

// 查找
func find(m map[int]string, num int) string {
  // 查找成功返回name, 并且ok为true
  // 查找失败, 返回name默认值, 并且ok为false
  name, ok := m[num]
  if ok {
    return name
  }
  return ""
}

// 删除键值对, 如果key不存在, 则什么也不做
func erase(m map[int]string, key int) {
  delete(m, key)
}

func main() {
  var m1 = make(map[int]string)
  createName(m1)
  ret := find(m1, 6)
  fmt.Printf("ret = %s\n", ret)
  show(m1)
  erase(m1, 1)
  show(m1)
}
