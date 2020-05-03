package main

import (
	"fmt"
	"sync"
	"time"
)

/*
  同步操作, 无非就是信号量和条件变量
  在Go中是
*/

var (
	tickets int = 20
	mtx     sync.Mutex
	wg      sync.WaitGroup
)

func main() {
	wg.Add(4)
	for i := 0; i < 4; i++ {
		go Sale(i)
	}
	wg.Wait()
}

func Sale(index int) {
	defer wg.Done()
	for {
		mtx.Lock()
		if tickets > 0 {
			time.Sleep(100 * time.Millisecond)
			fmt.Printf("窗口%d: 买了第%d张票\n", index, tickets)
			tickets--
			mtx.Unlock()
		} else {
			fmt.Printf("窗口%d: 没有票了\n", index)
			mtx.Unlock()
			break
		}
	}
}
