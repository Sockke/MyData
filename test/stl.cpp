/*
vector的扩容算法?
1. 如果说当前vector的容量为0, 那么为它分配1个字节大小的空间.
如果说当前的vector的容量大于0, 那么采用2倍扩容. 将先的数据拷贝到新的空间中.
2. 在vs下有所不同, 默认采用是1.5倍扩容的形式

malloc底层原理?
1. 对于小于128k的内存, 通过系统调用brk来实现, brk上移完成虚拟内存的分配, 当用户访问这块内存时
产生缺页, 建立虚拟内存与物理页的映射
2. 对于大于128k的内存, 通过系统调用mmap来实现, 这个在栈与堆之间的共享内存中进行一个分配,
目的是为了使大块内存能够及时的释放, 因为brk分配的内存, 是由释放顺序的, 高地址的内存先释放

虚拟内存与文件系统的联系?
1. 装载时期要建立虚拟内存与可执行程序的映射, 程序执行过程中对数据的访问产生缺页,
根据映射将可执行程序中的数据加载到物理内存中
2. swap分区暂时保存数据状态, 当物理内存不够用的时候, 需要通过页面调度将旧的页暂时保存到swap分区中
*/
