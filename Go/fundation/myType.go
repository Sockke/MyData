package main

import "fmt"

func main() {
	//arr := [...]int{9, 5, 2, 7}
	//pArr := &arr
	//showArr(pArr)
	//str := "hello world"
	//showString(&str)
	v := []int{9, 5, 2, 7}
	showSlice(v)
}

/*
	数组: 数组是一个对象, 底层是一个长度固定的数组
	在进行参数传递的时候是值语义, 会深拷贝整个数组
	因此在参数传递的时候, 传递数组的地址
	数组与数组的地址在访问或修改数组元素时具有类似的操作

	数组初始化的时候是根据下标进行初始化的
	arr := [...]int{9, 5, 2, 7}
	-> arr := [...]int{0: 9, 1: 5, 2: 2, 3: 7}

	数组提供了内置方法: len, cap
*/
func showArr(arr *[4]int) {
	for _, e := range arr {
		fmt.Printf("%d ", e)
	}
	fmt.Printf("\n")
}

/*
	字符串: 字符串底层是一个结构体, 结构体中包含了字节数组, 长度
	这也是为什么字符串不是切片但是却支持切片的功能
	由于字符串是只读的, 因此在语义上是值语义,
	在参数传递的过程中, 结构体是深拷贝, 但是底层的字节数组依然是指针的浅拷贝
	因此string的拷贝开销是固定的不依赖于数据大小, 作为参数传递不需要引用传递

	字符串类型可以与字节切片进行相互转换
*/
func showString(str string) {
	for _, e := range str {
		fmt.Printf("%c", e)
	}
	fmt.Printf("\n")
	bStr := []byte(*str)
	fmt.Printf("%T\n", bStr)
}

/*
	切片:底层是一个结构体, 包含了字节数组, 长度以及容量
	切片是Go中动态变化的数组结构, 切片操作灵活, 使用广泛
	切片是引用语义, 在参数传递的时候, 底层的字节数组指针是浅拷贝

	1. 为什么append需要返回一个切片
	因为Slice虽然是引用语义的数据类型, 但是它本身还是一个结构体,
	所谓的引用传递是指结构体中字节数组指针的浅拷贝, 而长度和容量是值语义,
	因此需要返回新的切片来更新len或cap

	2.切片的内存使用:
	由于切片是引用语义的数据类型, 在切片进行数据返回或数据删除时可能会存在
	遗留的数据引用问题, 这会影响GC对垃圾数据的及时回收, 对程序的性能增加负担,
	因此在Go中,有些情况下需要程序员适当的去进行值传递或对删除数据的置空操作,
	这也是Go中的内存管理的思想
*/

func showSlice(v []int) {
	for _, e := range v {
		fmt.Printf("%d ", e)
	}
	fmt.Printf("\n")

	fmt.Printf("len = %d, cap = %d\n", len(v), cap(v))

	/*
		// 尾插, 如果长度超过容量才会重新分配内存
		v = append(v, 100)
		v = append(v, 200, 300, 400, 500)
		fmt.Printf("len = %d, cap = %d\n", len(v), cap(v))
		// 尾插切片, 需要通过...进行解包, 头插也一样
		v = append(v, []int{9, 5, 2, 7}...)
		fmt.Printf("len = %d, cap = %d\n", len(v), cap(v))
		// 头插会导致重新分配内存, 效率较低
		//v = append([]int{200}, v...)
		//fmt.Printf("len = %d, cap = %d\n", len(v), cap(v))
	*/

	// 头删和尾删都只是指针的移动
	fmt.Printf("%p\n", v)
	v = v[:len(v)-1]
	fmt.Println(v)
	fmt.Printf("len = %d, cap = %d\n", len(v), cap(v))
	v = v[1:]
	fmt.Printf("len = %d, cap = %d\n", len(v), cap(v))
}
