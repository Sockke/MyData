package main

import (
	"encoding/json"
)

/*
	JSON:
	序列化: 将内存中的数据按照key-value的形式打包成磁盘或网络数据
	反序列化: 将磁盘或网络数据转换成内存中的数据
*/

type Info struct {
	Msg string
}
type Person struct {
	Name string
	Age  int
	Info
}

func main() {
	p1 := Person{"sock", 19, Info{"I like football"}}
	p2 := Person{"laoma", 20, Info{"I like smoking"}}
	p3 := Person{"xiaoqian", 18, Info{"I like shopping"}}
	p4 := Person{"liuchen", 19, Info{"I like eating"}}
	p5 := Person{"liuwei", 20, Info{"I like basketball"}}
	v := make([]Person, 0)
	v = append(v, p1)
	v = append(v, p2)
	v = append(v, p3)
	v = append(v, p4)
	v = append(v, p5)
	data, err := Serialization(v)
	if err != nil {
		fmt.Println("err:", err)
	} else {
		fmt.Println("data:", string(data))
	}

	names := make([]struct{ Name string }, 5)
	if Deserialization(data, names) != nil {
		fmt.Println("err:", err)
	} else {
		fmt.Println(names)
	}
}

func Serialization(v []Person) ([]byte, error) {
	return json.Marshal(v)
}

func Deserialization(data []byte, names []struct{ Name string }) error {
	return json.Unmarshal(data, &names)
}
