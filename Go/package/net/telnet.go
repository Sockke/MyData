package main

import (
  //"fmt"
	"io"
	"log"
	"net"
	"os"
  //"time"
)

func main() {
	// 创建套接字, 绑定地址信息, 发起连接
	conn, err := net.Dial("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
	}
	defer conn.Close()
	// 将socket中的数据copy到stdout中
	go mustCopy(os.Stdout, conn)
	// 将stdin中的数据copy到socket中
	mustCopy(conn, os.Stdin)
}

// Writer与Reader接口中分别实现了write与read方法
func mustCopy(w io.Writer, r io.Reader) {
	// 将Reader中的数据copy到Writer中, 遇到io.EOF结束
	if _, err := io.Copy(w, r); err != nil {
		log.Fatal(err)
	}
}
