package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

/*
  select一般用于监听通道的数据流动
  1. case只能判断IO操作, 比如说data<-channel
  2. 如果case命中, 则执行对应的处理, 如果多个case可以命中,
  则有任选一个进行处理
  3. 如果case没命中, 执行default, 没有default则阻塞等待
*/

func main() {
	channel1 := make(chan int)
	channel2 := make(chan int)

	isPrime := func(num int) bool {
		for i := 2; i <= int(math.Sqrt(float64(num))); i++ {
			if num%i == 0 {
				return false
			}
		}
		return true
	}
	go func() {
		rand.Seed(time.Now().Unix())
		randNum := rand.Intn(100) + 2
		if isPrime(randNum) {
			channel1 <- randNum
		} else {
			channel2 <- randNum
		}
	}()
	data := 0
	select {
	case data = <-channel1:
		fmt.Printf("%d是素数\n", data)
	case data = <-channel2:
		fmt.Printf("%d不是素数\n", data)
	}
}
