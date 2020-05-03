package main

import (
	"fmt"
	"sync"
	"time"
)

/*
	延迟初始化: 在某些场景下, 有些数据的初始化操作比较耗时, 如果在程序启动时就初始化会
	影响程序的启动速度, 因此会选择在需要的时候进行初始化

	因为初始化只能调用一次, 因此需要判断以及调用, 这个操作不是原子性的, 在并发的场景下会
	出现问题, 保证延迟初始化的安全性变得比较复杂

	在Go中通过sync.Once定义一个变量, 通过调用变量的Do方法来实现安全的初始化操作
	这个的底层原理与C++中mutex头文件下的std::call_once一样, 在底层维护一个bool值的变量,
	当第一次调用时, 加锁并将该变量从false设置为true, 下一次调用时判断变量的值即可
*/

var goods map[string]float64
var once_flag sync.Once

func initMap() {
	goods = make(map[string]float64)
	goods["apple"] = 2
	goods["orange"] = 1.5
	goods["banana"] = 3
	goods["peach"] = 5
	fmt.Println("once")
}

func findPrice(name string) float64 {
	once_flag.Do(initMap)
	return goods[name]
}

func main() {
	var price float64 = 0
	go func() {
		price = findPrice("banana")
		fmt.Println("banana:", price)
	}()
	go func() {
		price = findPrice("apple")
		fmt.Println("apple:", price)
	}()
	go func() {
		price = findPrice("orange")
		fmt.Println("orange:", price)
	}()
	time.Sleep(3 * time.Second)
}
