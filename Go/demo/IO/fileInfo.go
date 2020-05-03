package main

import (
  "fmt"
  //"os"
  "path/filepath"
)

func main() {
  // 文件信息的操作
  /*
  // 获取文件信息对象
  fileInfo, err := os.Stat("./pack1")
  if err != nil {
    fmt.Println(err)
    return
  }
  // 判断是否是文件夹
  fmt.Println("文件夹:", fileInfo.IsDir())
  // 输出文件名
  fname := fileInfo.Name()
  fmt.Println("文件名:", fname)
  // 输出文件大小
  fsize := fileInfo.Size()
  fmt.Println("文件大小:", fsize)
  // 输出文件权限
  fmt.Println("权限:", fileInfo.Mode())
  */

  // 路径的操作
  path1 := "./demo"
  path2 := "/home/sock/SaoLibrary/SaoLibrary/Go/fundation/demo"
  fmt.Println("是否是绝对路径:")
  fmt.Println("file1:", filepath.IsAbs(path1))
  fmt.Println("file2:", filepath.IsAbs(path2))
  // 获取绝对路径
  absPath, _ := filepath.Abs(path1)
  fmt.Println(absPath)
}
