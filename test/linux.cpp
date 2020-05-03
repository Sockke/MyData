/*
问你常见的几个命令:
查看磁盘: df -h 
查看内存: free -h
cat /proc/meminfo
查看cpu: 
cat /proc/cpuinfo
查看进程:
ps -ef | grep pname
查看tcp状态:
netstat -napt

awk
1. awk -F' ' '{print $1}' ./demo > newfile

硬链接与软链接
1. 硬链接文件, 类似于一个别名文件, 
硬链接文件与源文件的inode结点号相同.
2. 软链接文件, 类似于一个指针文件, 对应于Windows下快捷方式,
软链接文件与源文件是两个完全不同的文件, inode结点号不相同, 并且软链接文件inode结点中存储了源文件的地址

read与fread的区别?
1. read是系统调用, 是系统级别的. fread是库函数, 是对read的封装
2. fread在用户层实现了缓冲区, 对于较大数据的读取时会在用户层自主创建一块缓冲区,
用来减少系统调用的次数, 因为系统调用会产生80号中断陷入内核, 通过查表来执行内核处理函数,
再切换会用户态将结果返回, 开销是比较大的.

send与recv?
1. tcp连接双方都维护一个接收缓冲区与一个发送缓冲区,
recv是从接收缓冲区中取数据, 如果没有数据默认是阻塞挂起;
send是向发送缓冲区中写数据, 写完后直接返回, 此时数据不一定发送给对端. 如果缓冲区满了默认阻塞挂起.

fork的流程?
无论是fork, vfork, clone, 底层都是调用的do_fork
1. do_fork, 查找位图, 为子进程分配新的pid
2. 调用copy_process复制父进程的pcb, 虚拟地址空间, 文件描述符表等资源
3. 将子进程放到就绪队列中, 等待cpu的调度
同时pthread库中创建线程是通过clone来实现的, 因此在Linux中线程本质上仍然是进程,
只不过clone的标志位不同, 线程与进程共享资源的方式不同, 比如说fork需要拷贝虚拟地址空间, 而线程是共享虚拟地址空间.

Linux内核中哪些地方用到了红黑树?
1. 比如说epoll内核源码, 对于事件的存储是采用红黑树.
2. 比如说pcb中对于虚拟内存的管理, vm_area_struct是采用红黑树来组织的.

rpc与http的区别?
1. http是基于tcp的应用层的一个协议, 而rpc更趋向于一种框架
2. http定义了数据的格式, 对于数据封装相对更加臃肿, 而rpc没有严格定义数据的格式, 可以自定义消息的封装, 传输速度更快
3. http跨平台, 跨语言, 相对来说更加灵活, 只需要遵循接口规范即可,
rpc需要统一服务提供方与服务消费方的定义, 实现相对比较复杂.
4. http一般应用在一些小型的分布式场景中, 而rpc调用对用户更加透明, 效率更高, 一般应用在大型的分布式场景下.
*/
