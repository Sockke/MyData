package main

import (
  "fmt"
  "os"
  "io"
  "bufio"
)

/*
  bufio有关带缓冲区的io操作包
  比较常用的操作:
  1. NewReader/NewWriter来构造带缓冲的文件流对象
  2. bufio下的Read/Write进行读写文件, 使用Write时, 最后需要Flush刷新缓冲区
  3. ReadString/ReadBytes来通过字符来控制读取, 比如说读一行
*/

func main() {
  srcFile := "./demo"
  desFile := "./pack1/demo"
  total, err := CopyFileLine(srcFile, desFile)
  if err != nil {
    fmt.Println("下载失败")
  } else {
    fmt.Println("下载成功", total)
  }
}

// 1. 读文件
func CopyFile(srcFile, desFile string) (int64, error) {
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

  // 获取带buf的读文件对象
  bfp1 := bufio.NewReader(fp1)
  bfp2 := bufio.NewWriter(fp2)

  var total int64 = 0
  data := make([]byte, 1024)
  for {
    n, err := bfp1.Read(data)
    if n == 0 || err == io.EOF {
      break
    } else if err != nil {
      return total, err
    }
    total += int64(n)
    n, err = bfp2.Write(data[:n])
  }
  bfp2.Flush()
  return total, nil
}

func CopyFileLine(srcFile, desFile string) (int64, error) {
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

  bfp1 := bufio.NewReader(fp1)
  bfp2 := bufio.NewWriter(fp2)

  var total int64 = 0
  for {
    line, err := bfp1.ReadString('\n')
    if err == io.EOF {
      break
    } else if err != nil {
      return total, err
    }
    total += int64(len(line))
    bfp2.WriteString(line)
  }
  bfp2.Flush()
  return total, nil
}
