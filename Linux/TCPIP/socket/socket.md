## socket

#### 初始化

![image-20200531153527757](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200531153527757.png)

```c
// char buf[1024] = {0}
char buf[1024];
memset(buf, '\0', 1024);
/*
优势:
1. 解决了移植性问题, 并不一定所有的编译器在char buf[1024] = {0}时, 将后续所有字节都初始化为0
2. 性能高, vs编译器中可以看出char buf[1024] = {0}多了一个mov指令, gcc好像做了优化, 但还是建议使用后者, memset的效率是最高的
*/
```



#### socket一些重要的操作

* close与shutdown

```c++
/*
1. close时fd的引用计数-1, 只有当引用计数为0时才会断开连接.
在多进程环境下, 必须保证父子进程中都调用close, 才能断开连接
2. shutdown一般用在多进程环境下, 不管fd引用计数为几, 都会断开连接
shutdown(fd, SHUT_RDWR)
*/
```



* 带外标记(还需拓展)

```c++
/*
1. int sockatmart(int sockfd) 判断socket是否处于带外标记, 如果下一个读到的数据是带外数据, 则返回1, 否则返回0
2. 通过设置send/recv中的socket选项为MSG_OOB来收发带外数据
*/
```

* 地址信息函数

```c++
/*
1. getsockname获取socket本端的地址信息
getpeername获取socket连接远端的地址信息
2. 一般在不主动bind的客户端, 调用getsockname来获取本端的地址信息.
一般在服务端建立连接时, 调用getpeername来获取该连接对端的地址信息
*/
```

* socket选项

```c++
/*
设置地址重用:
1. 当sock处于TIME_WAIT状态时, 其绑定的地址信息依然可以被重用
*/
int reuse = 1;
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

/*
设置TCP收发缓冲区
1. 可以通过修改内核参数来修改TCP默认收发缓冲区的限制
/proc/sys/net/ipv4/tcp_rmem
/proc/sys/net/ipv4/tcp_wmem
2. 通过设置sock选项来修改TCP默认收发缓冲区的大小, 其值会加倍并且不能小于某个最小值(256)
*/
int sendbuf = SEND_BUF;
setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));

/*
设置TCP收发缓冲区的低水位标记:
1. 比如说接收数据, 当缓冲区中的数据达到低水位标记时, 就会通知应用程序从缓冲区中读取数据.
默认TCP收发缓冲区的低水位大小为1
2. SO_RCVLOWAT和SO_SNDLOWAT
*/

/*
设置close的行为标记:
1. close关闭连接, 默认是把socket缓冲区中的残留数据发送给对端
2. 可以通过修改SO_LINGER选项来修改默认行为
    struct linger {
     int l_onoff;  // 是否开启
     int l_linger;  // 滞留时间
    }
	1. l_onoff=0: 关闭, 即close为默认行为	
	2. l_linger=0: 丢弃缓冲区中残留的数据, 并给对端发送一个复位报文段(类似于异常关闭连接)
	3. l_linger>0: 滞留l_linger时间, 在这个时间内将缓冲区中残留的数据发送给对端,
	如果sock是阻塞的, l_linger时间内没有发送完毕, 返回-1, errno为EWOULDBLOCK.
	如果sock是非阻塞的, 直接返回, 通过判断返回值和errno来判断是否在时间内发送完毕
*/
```

* 网络信息api

```c++
/*
获取主机信息:
默认是先读取本机下的/etc/hosts, 如果获取失败会请求DNS
1. 根据主机名来获取: gethostbyname
2. 根据ip来获取: gethostbyaddr

获取服务信息:
读取本机下的/etc/services
1. 根据服务名来获取: getservbyname
2. 根据服务端口来获取: getservbyport

还有一些对上述接口进一步封装的api
getaddrinfo
getnameinfo
(查看man手册)
*/
```



#### 高级IO

* 管道(pipe和socketpair)

```c++
int pip2(int fd[2]);
/*
pipe创建一个管道, 用于进程间通信
1. pipe创建的管道本质上是在内核中创建一块缓冲区, 这个缓冲区是共享的, 并且保证了读写的原子性
2. 半双工通信, pipe[0]只能用于读, pipe[1]只能用于写
3. 默认是阻塞的, 管道中没数据读阻塞, 缓冲区满了写阻塞
4. 读写端的关闭会产生不同的行为, 写关闭, read返回0; 读关闭, write触发SIGPIPE异常

管道容量的默认大小为65536字节, 可以通过fcntl来改变它的容量
*/
```

```c++
// 双向管道
int socketpair(int domain, int type, int protocol, int sv[2]);
/*
socketpair创建一个双向管道
1. domain填写AF_UNIX, 因为socketpair只能在本机通信
2. 全双工通信, 两端的描述符既可以读也可以写
*/
```

* 重定向(dup与dup2)

```c++
int dup(int oldfd);
int dup2(int oldfd, int newfd);
/*
dup实现重定向
本质上就是复制 描述表表项 到另一个 表项
1. dup将描述符表中引用计数为0的最小表项 重定向到 oldfd, 重定向之前需要close(fd)
2. dup2将newfd 重定向到 oldfd, 重定向之前dup2会自动close(newfd)
*/
```

![image-20200531141642108](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200531141642108.png)

* 分散读和集中写(readv和writev)

```c++
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

struct iovec {
	void  *iov_base;    /* Starting address */
	size_t iov_len;     /* Number of bytes to transfer */
};
/*
readv实现分散读, writev实现集中写
对于分散在不同内存的数据, 可以通过readv一次分散读取, 或者将分散在不同内存中的数据, 通过writev集中写入. 减少了系统调用带来的开销.
*/
```

* 零拷贝

  * sendfile

  ```c++
  ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
  
  /*
  在内核中实现socket与本地文件之间的数据拷贝
  可以用于实现高效的大文件传输
  */
  ```

  * splice

  ```c++
  ssize_t splice(int fd_in, loff_t *off_in, int fd_out,
  			   loff_t *off_out, size_t len, unsigned int flags);
  
  /*
  在内核中实现socket与管道之间的数据拷贝
  可以用于实现高效的回射服务器
  */
  ```

  * tee

  ```c++
  ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags);
  
  /*
  在内核中实现两个管道之间的数据拷贝
  */
  ```



