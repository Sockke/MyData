package main

import (
	"fmt"
	"net/http"
)

/*
	ListenAndServe(url, obj): 启动服务器, obj为实现了指定interface的服务器对象, 可以为nil
	obj必须要实现Handler接口中的ServeHTTP方法, 该方法接收一个ResposeWriter用于响应信息,以及
	Request存储了请求的信息

	http.Request:
	1. 获取url中的信息
	req.URL.Path: 获取url中的path字符串
	req.URL.Query().Get("key"): 获取url中query中指定key的value

	http.ResponseWriter:
	1. 设置响应首行:
	res.WriteHeader(http.StatusNotFound)
	2.. 响应字符串信息:
	fmt.Fprintf(res, "", ...)

	但是, 一般在一个程序中只需要一个web服务器就足够了, 只是需要在服务器上注册指定的处理机制,
	只是在ListenAndServe中传递的服务器对象, 要求服务器对象具备实现Handler接口中唯一的ServeHTTP
	方法, 并且在这个方法中通过case来分发任务, 显得过于笨重和冗余
	Go中还为我们提供了更加灵活和轻便的处理方式:
	通过http.HandleFunc(url, handler)来将不同的url的处理直接分发到处理函数handler上, 而在
	http.ListenAndServe中的服务器对象传nil, 代表使用net/http下的一个默认服务器对象实例,
	它自动会将handler包装成实现了Handler接口中的ServeHTTP方法的对象, 只不过在这个ServeHTTP
	方法中调用了handler自身这个函数而已, 所以说自定义的handler的类型必须是与ServeHTTP类型一致
	原理:
	type HandlerFunc func(res http.ResponseWriter, req *http.Request)
	func (f HandlerFunc) ServeHTTP(res http.ResponseWriter, req *http.Request) {
		f(res, req)
	}
	也就是说你的这个服务器对象不再是一个实体了, 而是一个函数类型, 只要是满足这个函数类型就可以作为
	handler来处理对应的请求资源, 看似是一个服务器对应一个handler, 其实是一个服务器接收多个handler
*/

type database map[string]float32

func main() {
	db := database{"shoes": 25, "socks": 5}
	http.HandleFunc("/list", db.list)
	http.HandleFunc("/price", db.price)
	http.ListenAndServe("localhost:8000", nil)
}

func (db database) list(res http.ResponseWriter, req *http.Request) {
	for item, price := range db {
		fmt.Fprintf(res, "%s: %f\n", item, price)
	}
}
func (db database) price(res http.ResponseWriter, req *http.Request) {
	item := req.URL.Query().Get("item")
	price, ok := db[item]
	if !ok {
		res.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(res, "no such item:%s\n", item)
		return
	}
	fmt.Fprintf(res, "price:%f\n", price)
}

/*
func main() {
	db := database{"shoes": 50, "socks": 5}
	http.ListenAndServe("localhost:8000", db)
}

func (db database) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	// req.URL.Path: 获取路径path
	switch req.URL.Path {
	case "/list":
		for item, price := range db {
			fmt.Fprintf(res, "%s: %f\n", item, price)
		}
	case "/price":
		// 从查询字符串query中获取key为item的值
		item := req.URL.Query().Get("item")
		price, ok := db[item]
		if !ok {
			// 发送响应首行信息, 状态码
			res.WriteHeader(http.StatusNotFound)
			fmt.Fprintf(res, "no such item: %s\n", item)
			return
		}
		fmt.Fprintf(res, "price:%f\n", price)
	default:
		res.WriteHeader(http.StatusNotFound)
		fmt.Fprintf(res, "no such page")
	}
}
*/
