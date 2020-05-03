package main

import "fmt"

func main() {
  a := 1 // var a int = 1
  b := false // var b bool = false
  c := "sock" // var c string = "sock"
  d := 3.14 // var d float64 = 3.14
  ptr := &a // var ptr *int = &a

  fmt.Printf("a:%T\n", a)
  fmt.Printf("b:%T\n", b)
  fmt.Printf("c:%T\n", c)
  fmt.Printf("d:%T\n", d)
  fmt.Printf("ptr:%T\n", ptr)

  // 不允许++a, 并且不允许自增或自减表达式作为右值(ret = a++)
  a++
  fmt.Println("a:", a)
  ptr = nil // 空指针
}
