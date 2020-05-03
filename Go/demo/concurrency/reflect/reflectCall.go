package main

import (
  "fmt"
  "reflect"
)

/*
  通过反射, 来调用指定的方法或函数

  调用普通函数:
  1. 获取函数的Value对象
  method_value := reflect.ValueOf(func)
  2. 调用函数
  method_value.Call(nil) // 无参
  method_value.Call([]reflect.Value{reflect.ValueOf(10), reflect.ValueOf("hello"), ...})
  如果有返回值, 那么通过[]reflect.Value类型的数据来接收
  通过遍历, 调用Value.Interface()来获取实际返回值的内容

  调用成员函数:
  1. 获取结构体的Value对象
  i_value := reflect.ValueOf(obj)
  2. 获取其中的成员函数:
  method_value := i_value.MethodByName("Name")
  3. 调用函数
  method_value.Call(nil)
  method_value.Call([]reflect.Value{reflect.ValueOf(10), reflect.ValueOf("hello"), ...})
  如果有返回值, 那么通过[]reflect.Value类型的数据来接收
  通过遍历, 调用Value.Interface()来获取实际返回值的内容
*/

func main() {
  method_value := reflect.ValueOf(func1)
  method_value.Call(nil)
  fmt.Println("-------------------------")
  method_value = reflect.ValueOf(func2)
  results := method_value.Call([]reflect.Value{reflect.ValueOf(1), reflect.ValueOf("hello")})
  for i := 0; i < len(results); i++ {
    fmt.Println(results[i].Interface())
  }
}
func func1() {
  fmt.Println("func1, 没有参数, 没有返回值")
}
func func2(index int, msg string) (int, string){
  fmt.Println("func2, 有参数, 有返回值")
  return index, msg
}

/*
type Person struct {
  Name string
  Age int
}
func (p Person) Say(index int, msg string) string {
  fmt.Println("index:", index, "msg:", msg)
  return msg
}
func (p Person) ShowInfo() {
  fmt.Println(p)
}

func main() {
  p := Person{"sock", 19}
  i_value := reflect.ValueOf(p)
  method_value := i_value.MethodByName("Say")
  results := method_value.Call([]reflect.Value{reflect.ValueOf(1), reflect.ValueOf("hello")})
  for i := 0; i < len(results); i++ {
    fmt.Println(results[i].Interface())
  }
  fmt.Println("------------------------")
  method_value = i_value.MethodByName("ShowInfo")
  method_value.Call(nil)
}
*/
