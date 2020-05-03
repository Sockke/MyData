package main

import (
	"fmt"
)

// iota: 常量生成器
// iota在enum类型中, 从0逐行增加, 每次增加1, 可以规律初始化常量值
const (
	_ = 2 * iota
	A
	B
	C
)

func main() {
	showConst()
}

func showConst() {
	fmt.Println(A)
	fmt.Println(B)
	fmt.Println(C)
}
