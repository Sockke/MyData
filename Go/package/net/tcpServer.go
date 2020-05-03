package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
  //"io"
	//"strings"
	//"time"
)

/*
	启动一个打印当前时间的TCP服务器
*/
func main() {
	// 创建监听套接字, 绑定地址信息, 开始监听
	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}
	defer listener.Close()
	for {
		// 为连接分配新的套接字
		conn, err := listener.Accept()
		if err != nil {
			log.Fatal(err)
			continue
		}
		go handleConn(conn) // 处理连接
	}
}

/*
	Conn为一个接口类型, 这个接口中实现了Write, Read, Close等方法
*/
func handleConn(conn net.Conn) {
	defer conn.Close()
	// Conn接口类型中实现了read方法
	// 通过NewScanner获取接收对象
	input := bufio.NewScanner(conn)
	// 接收输入数据, 遇到'\n'结束
	for input.Scan() {
		// 打印输入数据, Text()返回缓冲区中的字符串
		//echo(conn, input.Text(), 1*time.Second)
    fmt.Fprintf(conn, "%s\n", input.Text())
	}
}

//func echo(conn net.Conn, say string, delay time.Duration) {
//	fmt.Fprintf(conn, "%s\n", strings.ToUpper(say))
//	time.Sleep(delay)
//	fmt.Fprintf(conn, "-%s-\n", strings.ToUpper(say))
//}

/*
func handleConn(conn net.Conn) {
	defer conn.Close()
	// WriteString(Writer, string), Writer接口实现了Write方法, 因此可以将Conn类型的对象传进去
	_, err := io.WriteString(conn, time.Now().Format("15:04:05\n"))
	if err != nil {
		return
	}
	time.Sleep(1 * time.Second)
}
*/
