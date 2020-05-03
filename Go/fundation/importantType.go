package main

import (
	"fmt"
)

type Info struct {
	msg string
}
type Person struct {
	Name string
	Age  int
	Info // 匿名结构体字段
}

/*
type Person struct {
	Name   string
	Age    int
	Gender string
	info   *Info
}
*/

func main() {
	//showSlice()
	//showMap()
	showStruct()
}

/*
	一些重要的复合类型: Slice/Map/Struct/JSON
	Slice: 类似于C++中的vector, 底层通过三个变量来动态的维护一个数组,
	这三个变量分别是数组首元素的地址, 长度, 容量
	Map: 类似于C++中的unordered_map, 底层是一个hash表
	Slice与Map生成的变量都是引用类型的变量
*/

/*
	1. []byte类型的切片可以与string类型进行直接转换
*/
func showSlice() {
	v := make([]int, 5)
	// 增加
	for i := 0; i < len(v); i++ {
		v[i] = i + 1
	}
	v = append(v, 100)
	// 修改
	v[0] = -100
	// 查询
	for _, e := range v {
		fmt.Printf("%d ", e)
	}
	fmt.Println()
	fmt.Println(v[:len(v)-1])
	fmt.Println(v[2:])
}

/*
1. Map中的value不能取地址赋值给一个变量, 因为Map底层是一个可以动态扩容的hash表,
value的地址可能会发生变化
*/
func showMap() {
	m := make(map[string]int)
	// 增加
	m["sock"] = 19
	m["laoma"] = 21
	m["liuchen"] = 19
	m["liuwei"] = 20
	for key, val := range m {
		fmt.Printf("name:%s, age:%d\n", key, val)
	}
	// 删除
	delete(m, "liuwei")
	// 修改
	m["sock"] = 21
	// 查询
	for key, val := range m {
		fmt.Printf("name:%s, age:%d\n", key, val)
	}
	if age, ok := m["sock"]; ok { // 可能出现key不存在的情况
		fmt.Println("age:", age)
	}
}

func showStruct() {
	/*
		// 这样写的好处是, 如果有字段忘记初始化, 会对该字段进行默认初始化
		p1 := Person{Name: "sock", Age: 19, Gender: "man"}
		p2 := Person{"laoma", 20, "man"}
		var p3 Person
		p3.Name = "xiaoqian"
		p3.Age = 18
		p3.Gender = "woman"
		// Go中摒弃了指针"->"访问, 指针访问结构体内容, 可以通过(*p).Name或p.Name
		p4 := new(Person)
		//*p4 = Person{"liuchen", 19, "woman"}
		p4.Name = "liuchen"
		p4.Age = 19
		p4.Gender = "woman"
		fmt.Println(p1)
		fmt.Println(p2)
		fmt.Println(p3)
		fmt.Println(*p4)

		// 结构体的比较
		p5 := Person{"sock", 19, "man"}
		fmt.Println(p1 == p5)
		fmt.Println(&p1 == &p5)
	*/

	/*
		p1 := new(Person)
		p1.Name = "sock"
		p1.Age = 19
		p1.Gender = "man"
		p1.info = new(Info)
		p1.info.msg = "I like football"
		fmt.Println(p1)
		fmt.Printf("name:%s, age:%d, gender:%s, info:%s\n", p1.Name, p1.Age, p1.Gender, p1.info.msg)
		p2 := Person{"laoma", 20, "man", &Info{"I like smoke"}}
		fmt.Println(p2)
	*/
	p1 := Person{"sock", 19, Info{"I like football"}}
	fmt.Println(p1)
	p2 := Person{Name: "laoma", Age: 20, Info: Info{"I like smoking"}}
	fmt.Println(p2)
	var p3 Person
	p3.Name = "xiaoqian"
	p3.Age = 18
	// 对于匿名结构体成员的访问, 可以直接访问叶子节点, 省略完整路径
	// 等价于p3.Info.msg
	p3.msg = "I like shopping"
	fmt.Println(p3)
}
