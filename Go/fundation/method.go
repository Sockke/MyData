package main

import (
	"fmt"
)

/*
	方法:
	Go中没有大众所接受的明确的OOP, 但是Go还是可以通过封装+组合来实现OOP
	并且Go中可以为任意类型添加方法, 这是Go的一大优势, 比如说可以为type []int切片添加方法
	1. 封装, 在Go中可以通过struct来包装对象的属性, 属性字段的首字母的大小写决定了
	该字段是否能够导出
	2. 组合, 在struct中可以嵌入struct, 达到组合的效果
*/
type Person struct {
	Name string
	Age  int
}
type v_int []int

// 通过指针来接收struct类型, 防止拷贝带来的性能消耗
func (p *Person) ShowInfo() {
	fmt.Println("name:", p.Name)
	fmt.Println("age:", p.Age)
}
func (v v_int) ShowSlice() {
	for _, e := range v {
		fmt.Printf("%v ", e)
	}
	fmt.Println()
}

func main() {
	p := Person{"sock", 19}
	// p是struct类型, 但是ShowInfo的接收器是*p, 因此是(&p).ShowInfo()
	// 但是Go编译器会根据接收器的类型, 自动对p进行取地址然后再进行调用
	p.ShowInfo()
	s := v_int{9, 5, 2, 7}
	s.ShowSlice()
}
