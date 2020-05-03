package main

import "net/rpc"

/*
  rpc接口模块, 对rpc服务的设计和注册提供接口
  主要包含三部分:
  1. rpc服务名
  2. rpc服务接口, 包含了提供的方法
  3. rpc服务注册
*/

// 服务名
const HelloServiceName = "./HelloService"

// 服务接口
type HelloServiceInterface interface {
  // 该服务所包含的方法
	Hello(req string, reply *string) error
}

// 注册rpc服务
func RegisterHelloService(service HelloServiceInterface) error {
	return rpc.RegisterName(HelloServiceName, service)
}

