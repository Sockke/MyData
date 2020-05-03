package main

/*
  strconv 有关整型与字符串类型的转换的包
  1. string -> int
  num, err := strconv.Atoi(str) 
  2. string -> int64
  num, err := strconv.ParseInt(str, 10, 64)
  3. int -> string
  str := strconv.Itoa(num)
  4. int64 -> string
  str := strconv.FormatInt(num, 10)
*/

/*
  strings 有关字符串操作的包
  1. 找到字符串所在的位置
  pos := strings.Index(str, "o")
  pos := strings.LastIndex(str, "o")    从右向左找第一个
  2. 字符串分割
  arr := strings.Split(str, " ")     返回字符串类型的切片
  3. 字符串拼接
  str := strings.Join(str, "")
*/

import (
  "fmt"
  "os"
  "io"
  "strings"
  "strconv"
  "log"
)

/*
  断点续传
  1. 打开或生成临时文件, 用来读取和更新已读数据大小
  2. 调整读写位置
  3. 边读边写, 同时更新临时文件的内容
  4. 全部正常完成后, 移除临时文件
*/

func main() {
  srcFile := "./demo"
  desFile := srcFile[strings.LastIndex(srcFile, "/") + 1 :]
  desFile = "./pack1/" + desFile
  Transfer(srcFile, desFile)
}

func Transfer(srcFile, desFile string) {
  tmpFile := desFile + "tmp.txt"
  // 打开文件
  fp1, err := os.Open(srcFile)
  HandleErr(err)
  fp2, err := os.OpenFile(desFile, os.O_CREATE | os.O_WRONLY, 0664)
  HandleErr(err)
  fp3, err := os.OpenFile(tmpFile, os.O_CREATE | os.O_RDWR, 0664)
  HandleErr(err)
  // 设置关闭文件
  defer fp1.Close()
  defer fp2.Close()
  // 1. 读取临时文件
  var total int64 = 0
  vTmp := make([]byte, 128, 128)
  fp3.Seek(0, io.SeekStart)
  count, err := fp3.Read(vTmp)
  if count != 0 {
    total, err  = strconv.ParseInt(string(vTmp[:count]), 10, 64)
    HandleErr(err)
  }
  // 2. 设置读写位置
  fp1.Seek(total, io.SeekStart)
  fp2.Seek(total, io.SeekStart)
  // 3. 边读边写
  data := make([]byte, 1024, 1024)
  for {
    n, err := fp1.Read(data)
    if n == 0 || err == io.EOF {
      // 移除临时文件
      fp3.Close()
      os.Remove(tmpFile)
      break
    }
    total += int64(n)
    n, err = fp2.Write(data[:n])
    // 更新临时文件
    fp3.Seek(0, io.SeekStart)
    fp3.WriteString(strconv.FormatInt(total, 10))
    //if total > 1000 {
    //  fmt.Println("断电")
    //  return
    //}
  }
  fmt.Println("下载成功")
}

func HandleErr(err error) {
  if err != nil {
    log.Fatal(err)
  }
}
