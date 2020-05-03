package main

import "fmt"

type Person struct {
  name string
  age int
  gender int
  number string
}

// 结构体的访问方式:
// 值传递访问与引用传递访问是一样的, 都是.
func show(p *Person) {
  fmt.Printf("name = %s\n", p.name)
  fmt.Printf("age = %d\n", p.age)
  fmt.Printf("gender = %d\n", p.gender)
  fmt.Printf("number = %s\n", p.number)
}
/*
func main() {
  //var p1 = Person{"sock", 19, 1, "5631076"}
  var p1 Person
  p1.name = "sock"
  p1.age = 19
  p1.gender = 1
  p1.number = "5631076" 
  show(&p1)
}
*/
func main() {
  // 可以通过key:value来指定初始化的顺序
  var p1 = Person{age:19, name:"sock", number:"5631076", gender:1}
  show(&p1)
  fmt.Println("---------------------")
  // 可以通过key:value来初始化一部分, 其他按默认值赋值
  var p2 = Person{name:"name", age:19}
  show(&p2)
}

