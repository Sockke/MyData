// 定义程序所在的包, package main表示go程序可以独立运行, 每个go程序都包含一个main包
package main

// 引入其他包(类似于C/C++引入头文件), "fmt"定义了格式化IO函数
import "fmt"

// 入口函数
func main() { // 左大括号不能单独放在一行
  fmt.Println("hello world") // 类似于 fmt.Print("hello world\n")
}
