package main

import (
	"log"
	"net"
	"net/rpc"
)

// rpc服务对象
type HelloService struct{}

// rpc服务对象必须满足rpc规则:
// 方法只能有2个参数, 且第二个参数是指针类型
func (service *HelloService) Hello(req string, reply *string) error {
	*reply = "hello:" + req
	return nil
}

func main() {
  // 注册rpc服务, 服务对象名为"HelloService", 服务对象的地址
	rpc.RegisterName("HelloService", new(HelloService))
	listener, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatal("Listen error:", err)
	}
	conn, err := listener.Accept()
	if err != nil {
		log.Fatal("Accept error:", err)
	}
  // 为新客户端连接提供rpc服务
	rpc.ServeConn(conn)
}
