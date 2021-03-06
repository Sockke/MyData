#### 阻塞与非阻塞, 同步与异步

* 简介

```
在处理IO的时候, 阻塞和非阻塞都是同步IO, 只有使用了特殊的API才是异步IO

在处理网络IO的时候, 会有2个阶段:
1. 数据准备

2. 数据读写

```

* 阻塞与非阻塞

```
数据准备阶段:
1. 这是讨论阻塞与非阻塞的阶段, 阻塞就是等待返回结果, 非阻塞就是不等待直接返回
2. 比如说recv, 如果sockfd是阻塞的, 那么如果没有数据可读, 就一直等待;
如果sockfd是非阻塞的, 无论是否有数据都直接返回
```

* IO的同步与异步

```
数据读写阶段:
1. 这是讨论IO同步与异步的阶段, 同步IO就是需要自己将内核缓冲区中的数据搬到应用缓冲区;
异步IO是系统将内核中的数据搬到用户提供的缓冲区中, 然后通知用户去进行数据读写.
2. 比如说recv就是一个同步IO, 无论是阻塞还是非阻塞都需要用户将内核缓冲区中的数据搬到应用缓冲区中才返回;
比如说Linux中的aio_read就是一个异步IO, 这是系统提供的特殊API来支持异步IO, 用户需要传入sockfd, buf, notice等重要的参数信息, 然后去做其他的事就可以了, 系统会将sockfd接收的数据从内核缓冲区搬到buf中, 然后根据用户提供的通知方式notice来通知用户进行数据读写.
```

* 业务的同步与异步

```
这里主要是指在多进程, 多线程环境下, 业务设计的方式.
同步就是指A需要阻塞等待B执行完毕之后才执行
异步就是指A不需要阻塞等待B执行完毕直接返回继续执行, 当B执行完毕后会通知A进行处理
```

#### 5种IO模型

* 阻塞IO

![image-20200914195740408](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200914195740408.png)

```
这是一个同步阻塞IO模型
1. 比如说像recv, 默认就是同步阻塞IO
2. 在数据准备阶段, 如果内核缓冲区没有数据即内核数据未准备好, 则进程一直阻塞
3. 数据就绪时进入在数据读写阶段, 应用进程将内核中的数据拷贝到应用缓冲区, 拷贝完成后返回
```



* 非阻塞IO

![image-20200914200447852](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200914200447852.png)

```
这是一个同步非阻塞IO模型
1. 比如像recv, 在通过fcntl设置socket默认属性(NONBLOCK)后, 是一个同步非阻塞IO
2. 在数据准备阶段, 不管内核中的数据是否准备好, 进程都直接报错返回(EAGAIN)
3. 数据就绪时进入数据读写阶段, 应用进程将内核中的数据拷贝到应用缓冲区, 拷贝完成后返回.
```



* IO复用

![image-20200914203026326](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200914203026326.png)

```
这是一个同步IO复用模型
1. 数据准备阶段, 通过select/poll/epoll IO复用接口来管理多个文件描述符资源, 并返回当前时刻下就绪的fd
2. 数据读写阶段, 需要读写的fd肯定是就绪的, 那么应用进程直接将内核中的数据拷贝到应用缓冲区, 拷贝完成后返回

优点:
1. 在一个进程下, 可以管理多个文件描述符资源, 并且直接对就绪的资源集进行串行化处理.
提高了cpu的利用率, 同时也提高了并发量
```



* 信号驱动

![image-20200914203124448](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200914203124448.png)

```
这是一个半同步半异步的IO模型
1. 数据准备阶段, 注册SIGNO信号处理程序, 应用进程可以干其他的事情. 
当内核数据准备好时, 会通过信号来通知应用进程并执行对应的信号处理程序
2. 在信号处理程序中, 进行数据读写, 该资源肯定是就绪的资源, 直接将内核缓冲区中的数据拷贝到应用缓冲区, 拷贝完成后返回
```



* 异步IO

![image-20200914203842095](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200914203842095.png)

```
这是一个异步IO模型
1. 系统提供的异步IO接口, 比如说Linux中的aio_read
2. 数据准备阶段与数据读写阶段都由内核来完成.
应用进程需要给内核提供应用缓冲区地址, 通知处理程序等信息, 内核去查看数据是否已经准备就绪, 如果准备就绪就将数据拷贝到应用进程提供的地址中, 拷贝完成后通知应用进程进行数据处理
```

#### IO复用

* select

```
采用事件集合的形式来组织事件, 底层是一个位图, 每种类型事件对应一个集合    
1. 创建事件集合, 并初始化    
2. 将用户关心的事件描述符添加到集合当中    
3. 调用select开始监听    
  将整个事件集合拷贝到内核中, 在内核中轮询遍历集合中的事件,    
  就绪的事件置1, 位就绪的事件置0, 然后将就绪事件集合拷贝到用户态,    
  遍历整个就绪集合, 对就绪的事件进行处理
```

* poll

```
采用事件结构的形式来组织事件, 统一了事件的处理    
1. 创建事件结构体数组.    
2. 将用户关心的事件结构添加到事件结构数组中    
3. 调用poll开始监听.    
  将整个事件结构拷贝到内核中, 在内核中轮询遍历数组中的事件结构,    
  当有事件就绪时, 将就绪的事件的revent进行一个标记, 然后将整个事件结构数组拷贝到用户态,    
  遍历整个事件结构数组, 判断revent, 对就绪事件进行处理 
```

* epoll

```
采用事件结构的形式来组织事件, 统一了事件的处理.                                                                                       
在内核中会创建一个eventpoll, 通过红黑树来存储关心事件, 双向链表来存储就绪事件  
1. 在内核中创建一个eventpoll结构体, 用来组织事件  
2. 将用户关心的事件添加到eventpoll中的红黑树中  
3. 调用epoll_wait开始监听.  
将用户关心的事件结构拷贝到内核中, 将事件挂在eventpoll中的红黑树中,   
当有事件到来时, 会调用事件回调函数, 将就绪事件添加到就绪链表中,  
内核通过判断就绪链表是否为空, 如果不为空, 则将就绪事件通过共享内存的形式  
返回给用户进行处理
```

* select, poll的缺陷

```
1. select每次都需要将事件集合拷贝到内核, 将就绪事件集合拷贝到用户态,
频繁的内核态与用户态的切换消耗很大
2. select监控采用轮询遍历的方式, 性能会随着事件描述符的增多而下降
3. select返回给用户的是整个事件集合, 用户还需要轮询遍历, 对就绪的事件进行操作
4. select采用事件集合的方式, 每种事件对应一种集合, 事件处理不统一,
并且事件描述符的数量有限制1024
```

```
与select的一样, 唯一一点优势在于,
poll采用事件结构的形式, 统一了事件的处理, 描述符资源的限制受限于系统资源, 而不是数组长度
```

* epoll的优势

```
1. epoll每次只需要将关心的事件结构拷贝到内核的红黑树中, 就绪的事件会放到内核的
双向链表中, 通过共享内存映射到用户态, 少了一次内核到用户态的数据拷贝
2. epoll不采用轮询遍历的方式监听, 而是采用回调函数, 当事件就绪时会自动调用
回调函数, 添加到就绪链表中, 性能不会随事件描述符的增多而下降.
3. epoll返回给用户的是都是就绪的事件, 用户不需要遍历判断, 直接可以进行操作
```

* LT与ET

```
1. LT水平出发, 当数据准备就绪时, 会触发事件, 如果当前线程对该事件的数据读写没有完成, 会继续触发该事件
2. ET边沿触发, 当数据从未准备就绪到准备就绪时, 会触发该事件, 无论当前线程对该事件的数据读写有没有完成, 都只触发一次

适用场景:
1. LT触发方式, 适合数据量比较大的场景, 为了使线程能够均匀的处理多个就绪的事件, 那么对于数据量比较大的就需要分多次进行读写
2. ET触发方式, 适合数据量小的场景, 线程保证对数据一次读写完毕, 减少触发次数, 提高性能
```

