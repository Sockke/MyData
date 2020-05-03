package main

import (
	"fmt"
	"log"
	"net/rpc"
)

func main() {
  // 请求rpc服务的连接
	client, err := rpc.Dial("tcp", "localhost:8000")
	if err != nil {
		log.Fatal("Connect error:", err)
	}
	var reply string
  // 请求rpc服务方法, Call("service.method", args...)
	err = client.Call("HelloService.Hello", "sock", &reply)
	if err != nil {
		log.Fatal("rpc service error:", err)
	}
	fmt.Println(reply)
}
