/*
gdb调试:
1. r 执行
2. n 单步调试
3. s 进入函数
4. p 查看对象的值
5. l 显示源代码
6. finish 跳出当前函数
7. b 断点
8. c 继续执行
9. bt 查看调用栈信息


gdb可视化调试:
gdb -tui ./main
cgdb ./main

gdb调试core文件:
1. ulimit -c 1024 设置core文件大小
2. 产生崩溃

gdb调试多线程:
1. info threads 查看当前进程中的线程信息
2. thread id 调试指定的线程

gdb调试多线程死锁问题:
1. 产生死锁的进程会被阻塞
2. 通过kill -11 pid杀死进程, 产生core文件
3. gdb ./main ./core.32532

gdb调试core文件, 发现全部都是一些地址信息, 原因是什么?
编译时加了-O的优化选项, 影响了调试.
*/
