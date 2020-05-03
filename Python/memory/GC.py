"""
    python的GC:
    引用计数为主, 标记清除与分代回收为辅

    1. 引用计数:
    python中每个对象的底层都维护了一个引用计数的字段obj_ref
    当有变量引用该对象时, 引用计数加1
    当有变量被del时, 引用计数减1
    2. 标记清除:
    想python中的容器类型, 比如说list, tuple, dict等可能会出现循环引用的问题
    循环引用会导致相互引用的对象不会再被使用, 但是引用计数不为0, 无法正常回收
    标记清除就是将容器类的对象通过引用关系来构成一个有向图, 根节点是一些全局变量,
    调用栈等不会被回收的对象, 从根节点出发对可达的对象添加标记, 不可达的对象
    可能存在循环引用的问题, 需要回收, 这样就解决了循环引用的问题
    3. 分代回收:
    对于对象的回收时机需要交给三个链表来处理, 分为年轻, 中年, 老年代.
    新创建的对象会放到年轻代, 当年轻代已满时, 触发GC, 将引用计数为0的对象回收,
    然后将没有被回收的对象放到中年代; 以此类推
"""