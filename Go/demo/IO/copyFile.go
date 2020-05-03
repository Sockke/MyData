package main

import (
  "fmt"
  "os"
  "io"
  "io/ioutil"
)

// 拷贝文件
// 1. 在性能方面, Copy要比直接使用Read/Write效率要高, 因为自定义切片难免会影响性能
// 2. 在拷贝大文件方面, io还支持CopyN, CopyBuffer等操作, Copy系列更加灵活
// 3. Copy系列函数底层都是对copyBuffer的封装, copyBuffer中依然是需要定义切片缓冲区

func main() {
  srcFile := "./demo"
  desFile := "./result3.cpp"
  n, err := CopyFile3(srcFile, desFile)
  if err != nil {
    fmt.Println("拷贝失败")
  } else {
    fmt.Println("拷贝成功", n)
  }
}

// 1. 使用io中的Read/Write来实现copy file
func CopyFile1(srcFile, desFile string) (int64, error) {
  fp1, err := os.Open(srcFile)
  if err != nil {
    return 0, err
  }
  fp2, err := os.OpenFile(desFile, os.O_CREATE | os.O_WRONLY, 0664)
  if err != nil {
    return 0, err
  }
  defer fp1.Close()
  defer fp2.Close()

  v := make([]byte, 1024, 1024)
  total := 0
  for {
    n, err := fp1.Read(v)
    if n == 0 || err == io.EOF {
      break
    } else if err != nil {
      return int64(total), err
    }
    total += n
    n, err = fp2.Write(v[:n])
  }
  return int64(total), nil
}
// 2. 使用io中的Copy来实现copy file
func CopyFile2(srcFile, desFile string) (int64, error) {
  fp1, err := os.Open(srcFile)
  if err != nil {
    return 0, err
  }
  fp2, err := os.OpenFile(desFile, os.O_CREATE | os.O_WRONLY, 0664)
  if err != nil {
    return 0, err
  }
  defer fp1.Close()
  defer fp2.Close()

  return io.Copy(fp2, fp1)
}
// 3. 使用ioutil中的ReadFile/WriteFile来实现copy file
// 只支持一次性读取, 大文件不适合
func CopyFile3(srcFile, desFile string) (int, error) {
  v, err := ioutil.ReadFile(srcFile)
  if err != nil {
    return 0, err
  }
  err = ioutil.WriteFile(desFile, v, 0664)
  if err != nil {
    return 0, err
  }
  return len(v), nil
}
