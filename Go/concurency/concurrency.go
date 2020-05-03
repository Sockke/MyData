package main

import (
	"sync"
)

/*
	Go中的并发模型: 并发编程的核心概念就是同步通信
	1. 通过sync.Mutex互斥锁来实现并发
	2. 通过channel通道来实现并发
	3. 通过sync.WaitGroup来实现并发
*/
//var mtx sync.Mutex
var wg sync.WaitGroup

func main() {
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			fmt.Println("hello world")
		}()
	}
	wg.Wait()
	/*
		ch := make(chan bool, 5)
		for i := 0; i < 5; i++ {
			go func() {
				fmt.Println("hello world")
				ch <- true
			}()
		}
		for i := 0; i < 5; i++ {
			<-ch
		}
	*/
	/*
		ch := make(chan bool)
		go func() {
			fmt.Println("hello world")
			ch <- true
		}()
		<-ch
	*/
	/*
		mtx.Lock()
		go func() {
			fmt.Println("hello world")
			mtx.Unlock()
		}()
		mtx.Lock()
	*/
}

