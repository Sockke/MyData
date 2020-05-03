package main

import (
	"fmt"
	"log"
  "net"
	"net/rpc"
  "net/rpc/jsonrpc"
)

/*
  rpc客户端, 主要对请求rpc服务连接及调用rpc服务方法进行封装
  使得客户端进行rpc服务方法调用的时候与在服务端本地调用一样,
  只需要知道方法名与参数列表即可, 不需要组织服务名与方法名
*/

// 继承rpc客户端的类
type HelloServiceClient struct {
	*rpc.Client
}

// 为该rpc服务的客户端, 封装rpc调用服务方法的接口
func (client *HelloServiceClient) Hello(req string, reply *string) error {
	return client.Client.Call(HelloServiceName+".Hello", req, reply)
}
// 封装请求指定rpc服务连接的接口
func DialHelloService(network, address string) (*HelloServiceClient, error) {
	//client, err := rpc.Dial(network, address)
  // 返回的conn为io.ReadWriteCloser类型的连接通道
	conn, err := net.Dial(network, address)
	if err != nil {
		return nil, err
	}
  // 为该连接通道建立rpc客户端的json编解码器
  client := rpc.NewClientWithCodec(jsonrpc.NewClientCodec(conn))
  return &HelloServiceClient{Client: client}, nil
}

func main() {
  // 请求rpc服务连接, 获取该服务的客户端对象
	client, err := DialHelloService("tcp", ":8000")
	if err != nil {
		log.Fatal("dial error:", err)
	}
  // 直接通过rpc客户端对象调用服务方法
	var reply string
	err = client.Hello("sock", &reply)
	if err != nil {
		log.Fatal("rpc call error:", err)
	}
	fmt.Println(reply)
}
