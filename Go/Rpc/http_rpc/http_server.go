package main

import (
  "io"
  "net/http"
  "net/rpc"
  "net/rpc/jsonrpc"
)

/*
  基于http的rpc服务端
  1. 注册rpc服务
  2. 为http请求提供响应方法
  3. 在方法中定义io.ReadWriteCloser类型的连接通道,
  将req与res来初始化通道, 最后为该连接通道建立json编解码器
  4. 启动http服务器
*/

type HelloService struct{}

func (service *HelloService) Hello(req string, reply *string) error {
  *reply = "hello:" + req
  return nil

}

func main() {
  // 注册rpc服务
  rpc.RegisterName("HelloService", new(HelloService))
  // 为http请求提供响应方法
  http.HandleFunc("/jsonrpc", func(res http.ResponseWriter, req *http.Request) {
    // 需要一个io.ReadWriteCloser类型的连接连接通道
    var conn io.ReadWriteCloser = struct {
      io.Writer
      io.ReadCloser
    }{
      Writer:     res, // json格式的rpc响应(result, error, id)
      ReadCloser: req.Body, // rpc请求数据(服务.方法, 参数, id)
    }
    // 为该连接通道建立json编解码器
    rpc.ServeRequest(jsonrpc.NewServerCodec(conn))
  })
  http.ListenAndServe(":9000", nil)
}

