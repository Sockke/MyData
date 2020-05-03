package main

import (
	"fmt"
	"reflect"
)

/*
什么是反射:
1. 反射就是在运行时期动态的获取对象的信息, 动态的调用对象的方法的机制.
为什么需要反射:
1. 在某些情况下我们不知道对象的类型, 同时无法得知对象有哪些方法可以调用,
此时根据反射与类型强相关的特性, 动态的获取对象的类型, 从而动态的调用对象的方法

Go中的反射包:
reflect.Type:  动态的获取和操作对象的类型信息
reflect.Value:  动态的获取和操作对象的值信息
*/

type Student struct {
	Name string
	Age  int
}

func (s *Student) Info() {
	fmt.Printf("My name is %s and I am %d years old\n", s.Name, s.Age)
}
func (s *Student) Say(something string) {
	fmt.Printf("%s say: %s\n", s.Name, something)
}

func main() {
	//callMethod()
	//getMethod()
	modifyVal()
}

// 根据对象的类型信息来调用对象的方法
func callMethod() {
	s := new(Student)
	s = &Student{Name: "sock", Age: 18}
	// 根据对象的地址唯一确定对象的值信息
	rval := reflect.ValueOf(s)
	// MethodByName根据函数名来查找函数
	method1 := rval.MethodByName("Info")
	if method1.IsValid() { // 判断函数对象是否有效
		// 无参, 可以通过[]reflect.Value{}或者nil
		method1.Call(nil)
	} else {
		fmt.Printf("no valid method\n")
	}
	method2 := rval.MethodByName("Say")
	if method2.IsValid() {
		// 参数为reflect.Value类型的切片
		args := []reflect.Value{
			reflect.ValueOf("hello world"),
		}
		method2.Call(args)
	} else {
		fmt.Printf("no valid method\n")
	}
}

// 根据对象的值信息, 遍历对象的所有函数名
func getMethod() {
	s := new(Student)
	s = &Student{Name: "laoma", Age: 20}
	rval := reflect.ValueOf(s)
	method_num := rval.NumMethod()
	for i := 0; i < method_num; i++ {
		method := rval.Method(i)
		fmt.Printf("method %d: %s\n", i, method.String())
	}
}

// 根据对象的值信息, 来修改对象的值
func modifyVal() {
	name := "sock"
	// 获取可取地址的反射对象的值信息
	// 必须是可取地址才行, ValueOf(&)获取对象的地址信息, Elem解引用, 获取可取地址的对象值信息
	rval := reflect.ValueOf(&name).Elem()
	rval.SetString("laoma")
	fmt.Printf("name = %s\n", name)

	s := new(Student)
	s = &Student{Name: "sock", Age: 18}
	rval = reflect.ValueOf(s).Elem()
	fmt.Printf("能否修改:%v\n", rval.CanSet())
}
