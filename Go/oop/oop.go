package main

import "fmt"

//type Info struct {
//	infos string
//}
//type Student struct {
//	Info
//	Name string
//	Age  int
//}
//
//func (s *Student) showInfo() {
//	fmt.Printf("my name is %s and I am %d years old, %s\n", s.Name, s.Age, s.infos)
//}
//func (s *Student) say(something string) {
//	fmt.Printf("%s say: %s\n", s.Name, something)
//}
type AnimalBehavior interface {
	Bark()
	Eat(string)
}
type Dog struct {
	Name string
}
type Cat struct {
	Name string
}

func (dog *Dog) Bark() {
	fmt.Printf("汪汪\n")
}
func (cat *Cat) Bark() {
	fmt.Printf("喵喵\n")
}
func (dog *Dog) Eat(food string) {
	fmt.Printf("dog %s eat %s\n", dog.Name, food)
}
func (cat *Cat) Eat(food string) {
	fmt.Printf("cat %s eat %s\n", cat.Name, food)
}

func main() {
	//a := []interface{}{123, "abc"}
	//showMore(a...)
	//showMore(a)

	//closure()

	//oop1()
	dog := new(Dog)
	dog = &Dog{Name: "德牧"}
	getEat(dog, "骨头")
	cat := new(Cat)
	cat = &Cat{Name: "蓝猫"}
	getEat(cat, "鱼")
}

// 不定参数的传入, 如果解包则类型为interface{}, 如果没解包则类型为[]interface{}
func showMore(more ...interface{}) {
	fmt.Println(more...)
}

// 闭包函数: 引用了外部作用域中变量的匿名函数
func closure() {
	for i := 0; i < 3; i++ {
		defer func() {
			fmt.Println(i) // i就是外部作用域中的变量
		}()
	}
}

/*
	oop: Go中的面向对象编程
	Go并不是一个传统的面向对象的语言, 但是具备实现oop的特性
	1. 通过结构体来描述对象的属性, 通过方法来描述对象的行为
	由于结构体与方法是绑定在一起的, 因此结构体以及对应的方法必须在同一个包内(内置类型不能绑定方法)
	2. 通过在结构体中组合匿名结构体来实现继承
	匿名结构体为基类, 当前结构体为派生类
	像C++/JAVA这种传统的面向对象语言, 多态是通过运行时的动态绑定来实现的(虚函数),
	但是Go中的结构体与方法是静态绑定的, 继承本质上是对结构体的组合, 因此无法实现多态
	3. 通过接口的抽象约定来实现多态
	接口是一种抽象类型, 该类型中约定了一些方法, 只要是实现了接口中所有方法的对象都都被定义为这种接口类型
	Go的面向对象之所以叫鸭子面向对象, 是由于接口的特性, 只要是像鸭子就可以被当成鸭子来看待
	Go中的接口是由2部分组成, 分别是类型与值, 通过接口来接收对象是一种动态的绑定(我猜是通过反射来确定值)
*/
//func oop1() {
//	s := new(Student)
//	s = &Student{Info: Info{"I like football"}, Name: "sock", Age: 18}
//	s.showInfo()
//	s.say("hello world")
//}
// 多态
func getEat(animal AnimalBehavior, food string) {
	animal.Bark()
	animal.Eat(food)
}
