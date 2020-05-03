package main

import (
	"fmt"
	"sort"
)

/*
	sort包:
	要对一组数据进行排序, sort中的大部分函数接收一个接口interface,
	该interface必须实现了Len, Less, Swap这三种方法
	即长度, 比较器, 交换器
	1.
	sort.IntSlice(arr): 对[]int类型的切片包装添加三种方法
	sort.StringSlice(arr): 对[]string类型的切片包装添加三种方法
	...
	从小到大: sort.Sort(sort.IntSlice(arr)) / sort.Sort(sort.StringSlice(arr))
	 		 sort.Ints(arr) / sort.Strings(arr)
	从大到小: sort.Sort(sort.Reverse(sort.IntSlice(arr)))
	*Reverse仅仅是对数据集下标的反转, 需要结合sort.Sort函数*
	2.
	自定义Len, Less, Swap
*/

/*
type MyPerson struct {
	Name string
	Age  int
}
// 定义一个结构体类型, 里面存放了待排数据集以及自定义比较器
type Persons struct {
	Pers      []*MyPerson
	myCompare func(left, right *MyPerson) bool
}
// 为待排类型添加interface所需的Len, Less, Swap方法
func (p Persons) Len() int {
	return len(p.Pers)
}
func (p Persons) Less(i, j int) bool {
	// 在比较方法中直接返回自定义的比较器
	return p.myCompare(p.Pers[i], p.Pers[j])
}
func (p Persons) Swap(i, j int) {
	p.Pers[i], p.Pers[j] = p.Pers[j], p.Pers[i]
}

func main() {
	persons := []*MyPerson{
		{"sock", 19},
		{"laoma", 20},
		{"liuchen", 19},
		{"xiaoqian", 18},
	}
	sort.Sort(Persons{persons, func(left, right *MyPerson) bool {
		return left.Age < right.Age
	}})
	for _, e := range persons {
		fmt.Println(e)
	}
}
*/

func main() {
	showSort()
}

func showSort() {
	// 简单的排序切片
	arr1 := []int{9, 5, 2, 7}
	// 从小到大
	//sort.Sort(sort.IntSlice(arr1))
	// 从大到小
	sort.Sort(sort.Reverse(sort.IntSlice(arr1)))
	for _, e := range arr1 {
		fmt.Printf("%d ", e)
	}
	fmt.Println()
}
