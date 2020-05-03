package main

import (
  "fmt"
  //"io"
  "io/ioutil"
)

/*
  ioutil是io包下的一个辅助包
  主要是方便对小文件进行简单的读写, 以及对目录信息的统计等
*/

func main() {
  path := "."
  TraverseDirAll(path)
  //data, err := ReadFile(path)
  //if err != nil {
  //  fmt.Println("err:", err)
  //  return
  //}
  //fmt.Println(string(data))
  //n, err := WriteFile(path)
  //if err != nil {
  //  fmt.Println("err:", err)
  //  return
  //}
  //fmt.Println("n:", n)
}

// 遍历当前目录下的所有文件
func TraverseDir(path string) {
  files, err := ioutil.ReadDir(path)
  if err != nil {
    fmt.Println("err:", err)
  }
  for i := 0; i < len(files); i++ {
    fmt.Printf("index:%d, fname:%s, isDir:%t\n", i, files[i].Name(), files[i].IsDir())
  }
}

// 递归遍历当前目录下的所有除目录以外的文件
func TraverseDirAll(startPath string) {
  files, err := ioutil.ReadDir(startPath)
  if err != nil {
    fmt.Println("err:", err)
  }
  for _, file := range files {
    path := startPath + "/" + file.Name()
    if file.IsDir() {
      TraverseDirAll(path)
    } else {
      fmt.Printf("fname:%s\n", path)
    }
  }
}

// 读取小文件
func ReadFile(srcFile string) ([]byte, error) {
  data, err := ioutil.ReadFile(srcFile)
  if err != nil {
    return []byte{}, err
  }
  return data, nil
}

// 写小文件
func WriteFile(desFile string) (int, error) {
  dataStr := "sock is a good man"
  data := []byte(dataStr)
  err := ioutil.WriteFile(desFile, data, 0664)
  if err != nil {
    return 0, err
  }
  return len(dataStr), nil
}
