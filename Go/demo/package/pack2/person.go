package pack2

import "fmt"

func init() {
  fmt.Println("this is person struct")
}

type Person struct {
  Name string
  age int
  Gender string
}
