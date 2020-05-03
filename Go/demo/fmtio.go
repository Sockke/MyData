package main

import (
  "fmt"
)

func main() {
  //FmtIO()
  //fmt.Println("---------------")
  name := ScanLine()
  age := 0
  fmt.Scanln(&age)
  fmt.Println(name, age)
}

// fmt
func FmtIO() {
  // fmt输入
  name := ""
  age := 0
  fmt.Scanf("%s", &name)
  fmt.Scanf("%d", &age)
  //fmt.Scanln(&name)
  //fmt.Scanln(&age)
  // fmt输出
  fmt.Println(name, age)
}

func ScanLine() string {
  var err error = nil
  v := []byte{}
  for err == nil {
    var c byte
    _, err = fmt.Scanf("%c", &c)
    if c != '\n' {
      v = append(v, c)
    } else {
      break
    }
  }
  return string(v)
}

