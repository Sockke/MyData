package main

import "fmt"

type Car interface {
  show()
}

type MyCar struct {
  name string
}

func (car *MyCar) show() {
  fmt.Printf("my car's name:%s\n", car.name)
}

func main() {
  car1 := new(MyCar)
  car1.name = "Benz"
  car1.show()
  //car2 := new(MyCar)
  //car2.name = "Audi"
  //car2.show()
}
