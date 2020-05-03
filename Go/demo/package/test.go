package main

import (
  "fmt"
  "./pack1/pack12"
  "./pack2"
)

func init() {
  fmt.Println("this is main function")
}

func main() {
  result := pack12.Add(3, 5)
  fmt.Printf("result = %d\n", result)
  result = pack12.Multi(3, 5)
  fmt.Printf("result = %d\n", result)

  p := pack2.Person{Name: "sock", Gender: "男"}
  fmt.Println(p)
}
