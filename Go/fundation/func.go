package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	/*
		// 最简单的匿名函数
		a := func() int {
			return 1
		}()
		fmt.Println(a)
		b := func(a int) int {
			return a
		}(a)
		fmt.Println(b)

		// 保存匿名函数的地址
		// 由于函数值是引用类型, 匿名函数地址被保存下来, 匿名函数中对外部变量的引用也会被保存下来
		// 在Go/Python中把函数值叫做闭包
		f := addVal()
		fmt.Println(f())
		fmt.Println(f())
		fmt.Println(f())
		fmt.Println(f())
	*/

	/*
		// 函数的不定参数
		sum := getSum(2, 5, 7, 9)
		fmt.Println("sum:", sum)
		v := []int{9, 5, 2, 7}
		sum = getSum(v...)
		fmt.Println("sum:", sum)
	*/

	/*
		// defer机制, 类似于C++中的RAII, 让一些管理资源的代码在函数生命周期结束之前被调用
		fname := "./demo"
		data, err := ReadFile(fname)
		if err != nil {
			fmt.Println("err:", err)
		} else {
			fmt.Println("data:", string(data))
		}
	*/

	// panic("err"): 类似于C/C++中的断言, 一般用于严重性错误, 使得程序直接崩溃
	// recover(): 捕获异常, 在defer中设置捕获异常的函数, 如果程序发生异常会被recover捕获到,
	// 可以避免程序因为异常而直接退出
	a, b := 2, 0
	division(a, b)
}

// 闭包
func addVal() func() int {
	var a int
	return func() int {
		a++
		return a
	}
}

// 不定参
func getSum(vals ...int) int {
	sum := 0
	for _, e := range vals {
		sum += e
	}
	return sum
}

// defer
func ReadFile(fname string) ([]byte, error) {
	fp, err := os.Open(fname)
	if err != nil {
		return nil, err
	}
	defer fp.Close()
	return ioutil.ReadAll(fp)
}

func division(a, b int) {
	// 异常处理
	defer func() {
		if p := recover(); p != nil {
			fmt.Println("err:", p)
		}
	}()
	if b == 0 {
		panic("分母是0") // 断言
	} else {
		fmt.Println("result:", a/b)
	}
}
