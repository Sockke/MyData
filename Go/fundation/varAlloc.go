package main

/*
	编译器在栈上, 还是在堆上分配空间不由变量的定义方式决定(var, new)
	Go编译器为了考虑安全和性能, 会对用户的选择做出优化
*/

var gp *int

func main() {

}

// 因为gp是全局变量, 它所引用的变量必须是在堆中分配的, 否则局部变量会发生逃逸
func gfunc() {
	ret := 1
	gp = &ret
}

// 因为ret变量不会发生逃逸, 所以可以在栈上分配, 也可以在堆上分配然后由GC回收
func lfunc() {
	ret := new(int)
	*ret = 10
}

/*
func getStr() *int {
	v := 1
	return &v
}
*/
