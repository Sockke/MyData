package main

import (
  "fmt"
	"bufio"
	//"io"
	"log"
	"net"
	"time"
)

func main() {
	// 开始监听
	listener, err := net.Listen("tcp", "localhost:8000")
	if err != nil {
		log.Fatal(err)
		return
	}
	defer listener.Close()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Fatal(err)
			time.Sleep(100 * time.Millisecond)
			continue
		}
		go handleConn(conn)
	}
}

func handleConn(conn net.Conn) {
	defer conn.Close()
	input := bufio.NewScanner(conn)
	for input.Scan() {
    fmt.Fprintf(conn, "%s\n", input.Text())
	}
}
