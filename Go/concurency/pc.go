package main

import "fmt"

/*
	通过channel实现生产者消费者模型
*/
func main() {
	ch := make(chan int, 3)
	go producer(ch)
	consumer(ch)
}

func producer(ch chan<- int) {
	for i := 0; i < 6; i++ {
		ch <- i
	}
	close(ch)
}
func consumer(ch <-chan int) {
	for e := range ch {
		fmt.Println(e)
	}
}
