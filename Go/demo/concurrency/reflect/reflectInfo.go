package main

import (
  "fmt"
  "reflect"
)

/*
  反射就是在运行时期, 动态的获取变量的类型信息
  有些时候我们需要根据这个变量的类型信息, 去决定做什么事情
  或者我们会调用具有这个类型信息的函数, 
  比如说google的grpc, 远程调用会根据请求中包含的类型信息来确定调用本地的哪个方法

  go中reflect包中提供了有关反射的相关接口
  1. 获取变量的类型信息
  i_type := reflect.TypeOf(obj)
  获取类型名: i_type.Name()
  获取类型: i_type.Kind() 
    返回reflect.Kind, 比如说reflect.Struct, reflect.Int64
  2. 获取变量的内容信息
  i_value := reflect.ValueOf(obj)

    获取结构体变量的内容信息
    获取字段数: i_type.NumField()
    获取字段信息: field := i_type.Field(i)
      field.Name, field.Type
    获取字段内容: i_value.Field(i).Interface()

*/

type Info struct {
  Name string
  Age int
  Gender string
}

func (info Info) Say(msg string) {
  fmt.Printf("%s say:%s\n", info.Name, msg)
}
func (info Info) ShowInfo() {
  fmt.Printf("name:%s, age:%d, gender:%s\n", info.Name, info.Age, info.Gender)
}

func main() {
  p1 := Info{"sock", 19, "男"}
  showInterfaceInfo(p1)
}

func showInterfaceInfo(input interface{}) {
  i_type := reflect.TypeOf(input)
  fmt.Println("type name:", i_type.Name())
  fmt.Println("type kind:", i_type.Kind())

  // 如果传入的是结构体
  if i_type.Kind() == reflect.Struct {
    for i := 0; i < i_type.NumField(); i++ {
      field := i_type.Field(i)
      field_value := reflect.ValueOf(input).Field(i).Interface()
      fmt.Printf("field :%s,field type:%s,field value:%v\n", field.Name, field.Type, field_value)
    }
    for i := 0; i < i_type.NumMethod(); i++ {
      method := i_type.Method(i)
      fmt.Printf("method:%s, method type:%s\n", method.Name, method.Type)
    }
  } else { // 如果不是结构体
    i_value := reflect.ValueOf(input)
    fmt.Println("value:", i_value)
  }
}
