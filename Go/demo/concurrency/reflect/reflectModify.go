package main
import (
  "fmt"
  "reflect"
)

/*
  通过反射来修改对象的值, 本质上是根据对象的地址与对象的类型信息来修改

  1. 获取变量的内容对象, 必须是引用类型
    i_value := reflect.ValueOf(obj)
  2. 创建反射对象
    r_value := i_value.Elem()
  3. 判断反射对象是否能修改
    r_value.CanSet()
  4. 修改反射对象
    r_value.SetInt(10) / r_value.SetString("sock")
    修改结构体类型的反射对象, 修改指定字段
    r_field_value := r_value.FieldByName("Name")
    r_field_value.SetInt(10)...
    
*/

type Info struct {
  Name string
  Age int
  Gender string
}

func main() {
  p := Info{"sock", 19, "男"}
  fmt.Println(p)

  // 获取对象地址的内容信息
  i_value := reflect.ValueOf(&p)
  if i_value.Kind() == reflect.Ptr {
    // 获取反射对象
    r_value := i_value.Elem()
    if !r_value.CanSet() {
      return
    }
    f1 := r_value.FieldByName("Age")
    f1.SetInt(20)
  }

  fmt.Println(p)
}

