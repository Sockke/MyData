package main

import "fmt"

/*
	n个channel可以连接n + 1个goroutine
	数据可以在被多个channel连接起来的goroutine组中进行传递
	对于没有多余数据要发送的channel, 可以通过close来关闭它, 防止死锁
	同时对于从channel中获取数据可以通过range来迭代

	channel的单向传输, 一般是作为参数来限制channel的行为,
	防止在函数中滥用导致一些问题
*/
func main() {
	channel := make(chan int)
	go Send(channel)
	Recive(channel)
	/*
		channel1 := make(chan int)
		channel2 := make(chan int)
		num := 10
		go func() {
			channel1 <- num
		}()

		go func() {
			data := <-channel1
			data *= 10
			channel2 <- data
		}()

		data := <-channel2
		fmt.Println("data:", data)
	*/
}

// 只能向channel中发送数据
func Send(channel chan<- int) {
	for i := 0; i < 10; i++ {
		channel <- i
	}
	close(channel)
}

// 只能从channel中获取数据
func Recive(channel <-chan int) {
	for e := range channel {
		fmt.Printf("%d ", e)
	}
	fmt.Println()
}
