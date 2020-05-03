/*
[两台主机进行通信, 如何查看经过了哪些路由器]:
1. tracetoute www.baidu.com
windows: tracert www.baidu.com
(默认最大的跃点跟踪数量是30)
2. ping -R www.baidu.com
(我记得ping受头部长度的限制, 最多能记录9个路由信息)

[数据在7层模型中是如何传输的]:
在应用层产生数据, 到达表示层对数据进行一些压缩, 编码等操作, 在会话层为数据传输建立一个会话.
数据到达传输层后, 封装源端口目的端口等信息, 如果是基于tcp协议根据mss进行数据的分段.
数据到达网络层后, 封装源ip与目的ip等信息, 如果是基于udp的话根据mss可能会进行数据的分片.
数据到达链路层后, 封装帧头帧尾, 源MAC与目的MAC地址(目的MAC地址可能需要通过arp广播来进行获取)等信息, 封装成数据帧.
数据帧到达物理层, 转换成比特流在网络中进行传输.

三次握手对应哪个socket函数?
1. 客户端调用connect, 向服务器发送syn请求.
2. 服务端通过listen, 返回ack与syn.
3. 客户端收到响应后, 发送ack返回.
4. 服务端接收到ack后, 将该连接从未完成连接队列移动到已完成连接队列中, 等待accept从队列中取出

dns解析的过程?
1. 首先先检查浏览器缓存中是否有该域名映射的ip.
2. 再去/etc/hosts文件中查询是否有该域名的映射ip.
3. 请求本地dns服务器, 如果没有, 可能会请求根dns服务器进行递归转发
最终查询到的数据返回本地dns服务器.
*/


