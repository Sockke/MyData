package main

import (
	"fmt"
)

/*
	error是接口类型, 在接口中声明了Error()方法用于获取错误字符串
	有关错误信息的函数, 大部分在底层都依赖实现了error接口的对象

	 Errorf底层调用了errors.New, errors.New底层返回了errstring结构体对象
	 errstring结构体对象实现了error这个接口中的方法
	 也就是说所有的错误处理函数的底层都是调用了errstring结构体对象,
	 这个对象实现了error接口中的Error方法
*/

func main() {
	// fmt.Errorf的使用场景比较广泛, 因为使用灵活
	err := fmt.Errorf("this is a error:%d\n", 1)
	fmt.Println("err:", err) // 底层调用了err.Error()
}

