package main

import (
	"log"
	"net"
	"net/rpc"
  "net/rpc/jsonrpc"
)

/*
  rpc服务端, 定义rpc服务对象
*/

// 声明rpc服务对象的类型
type HelloService struct{}

// 为rpc服务添加方法, 方法参数必须是2个且第二个为指针, 返回值为error
func (service HelloService) Hello(req string, reply *string) error {
	*reply = "Hello:" + req
	return nil
}

func main() {
  // 注册rpc服务
	RegisterHelloService(new(HelloService))
  // tcp服务端开始监听
	listen, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatal("listen error:", err)
	}
	for {
    // 监听套接字获取新连接
		conn, err := listen.Accept()
		if err != nil {
			log.Fatal("accept error:", err)
		}
    // 为该连接提供rpc服务
		//go rpc.ServeConn(conn)
    // 提供rpc服务, 并且为rpc服务端建立json编解码器
    go rpc.ServeCodec(jsonrpc.NewServerCodec(conn))
	}
}
