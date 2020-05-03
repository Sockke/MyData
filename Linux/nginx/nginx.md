## nginx

#### 重要的结构体和变量:

```c
// 内存池的结构体
struct ngx_pool_s {
    ngx_pool_data_t       d; // 小块内存的信息
    size_t                max;  // 小块内存最大的空闲空间的大小
    ngx_pool_t           *current; // 当前的小块内存
    ngx_chain_t          *chain; 
    ngx_pool_large_t     *large; // 大块内存的起始位置
    ngx_pool_cleanup_t   *cleanup; // 内存池中的对象在堆上开辟的内存
    ngx_log_t            *log;
};
// 重命名
typedef struct ngx_pool_s	ngx_pool_t;
```



```c
// 内存池中小块内存信息结构体
typedef struct {
    u_char               *last; // 小内存块中空闲内存的起始位置
    u_char               *end; // 小内存块的末尾
    ngx_pool_t           *next; // 指向下一个小内存块
    ngx_uint_t            failed; // 该小内存块分配内存失败的次数
} ngx_pool_data_t;
```



```c
// 小内存块最大大小, 4096-1, 一个内存页的大小
#define NGX_MAX_ALLOC_FROM_POOL  (ngx_pagesize - 1)
// 默认内存池的大小
#define NGX_DEFAULT_POOL_SIZE    (16 * 1024)
// 内存池的对齐数
#define NGX_POOL_ALIGNMENT       16
```



#### 内存池的创建

```c
// 内存池的创建函数
ngx_pool_t *
ngx_create_pool(size_t size, ngx_log_t *log)
{
    ngx_pool_t  *p;
	
    // 为内存池开辟内存
    p = ngx_memalign(NGX_POOL_ALIGNMENT, size, log);
    if (p == NULL) {
        return NULL;
    }

    // 初始化操作
    p->d.last = (u_char *) p + sizeof(ngx_pool_t); // last指向当前小内存块中空闲内存的起始位置
    p->d.end = (u_char *) p + size; // end指向当前小内存块的末尾 
    p->d.next = NULL; 
    p->d.failed = 0;

    size = size - sizeof(ngx_pool_t); // 小内存块中空闲内存的大小
    // 如果size<4095, 那么max=size, 否则, max=4095
    // max就是小内存块中能够分配的最大空闲内存
    p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    p->current = p; // current指向当前的小内存块
    p->chain = NULL; 
    p->large = NULL;
    p->cleanup = NULL;
    p->log = log;

    return p;
}
```



```c
#define ngx_memalign(alignment, size, log)  ngx_alloc(size, log)
// 内存开辟, 直接通过malloc来申请一块内存
void *
ngx_alloc(size_t size, ngx_log_t *log)
{
    void  *p;

    p = malloc(size);
    if (p == NULL) {
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,
                      "malloc(%uz) failed", size);
    }

    ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, log, 0, "malloc: %p:%uz", p, size);

    return p;
}
```



#### 向内存池申请内存

```c
// ngx_pallloc向内存池中申请内存
void *
ngx_palloc(ngx_pool_t *pool, size_t size)
{
#if !(NGX_DEBUG_PALLOC)
    // max是pool中小块内存中空闲内存的最大大小
    // 如果是小块内存, 那么按小块内存的分配来处理
    if (size <= pool->max) {
        return ngx_palloc_small(pool, size, 1);
    }
#endif
	// 如果是大块内存, 那么按大块内存的分配来处理
    return ngx_palloc_large(pool, size);
}
```



```c
// 按小块内存来分配
static ngx_inline void *
ngx_palloc_small(ngx_pool_t *pool, size_t size, ngx_uint_t align)
{
    u_char      *m;
    ngx_pool_t  *p;

    p = pool->current; // p指向了可以分配的第一个小内存块

    do {
        m = p->d.last; // m指向当前小内存块中空闲内存的起始位置

        // 内存对齐
        if (align) {
            m = ngx_align_ptr(m, NGX_ALIGNMENT);
        }

        // 当前小内存块中剩余的空闲内存足够
        if ((size_t) (p->d.end - m) >= size) {
            p->d.last = m + size; // 移动一下last指针

            return m;
        }

        // 当前小内存块中剩余的空闲内存不够, 那就让p指向下一个小内存块
        p = p->d.next;

    } while (p);

    // 内存池中, 没有小内存块可以分配出size大小的内存
    // 分配一块新的小块内存
    return ngx_palloc_block(pool, size);
}

// 分配一块新的小块内存
static void *
ngx_palloc_block(ngx_pool_t *pool, size_t size)
{
    u_char      *m;
    size_t       psize;
    ngx_pool_t  *p, *new;

    // psize表示小块内存的大小
    psize = (size_t) (pool->d.end - (u_char *) pool);

    // 通过malloc来申请psize大小的内存块
    m = ngx_memalign(NGX_POOL_ALIGNMENT, psize, pool->log);
    if (m == NULL) {
        return NULL;
    }

    new = (ngx_pool_t *) m; // new指向了新分配的小内存块

    // 对新分配的小内存块进行初始化操作
    new->d.end = m + psize; // end指向小内存块的末尾
    new->d.next = NULL; 
    new->d.failed = 0;

    m += sizeof(ngx_pool_data_t); // m指向了小内存块中空闲内存的起始位置
    m = ngx_align_ptr(m, NGX_ALIGNMENT); // 内存对齐
    new->d.last = m + size; // last偏移, 分配出size大小的内存

    // p移动到最后一个小块内存
    for (p = pool->current; p->d.next; p = p->d.next) {
        // 移动过程中要更新每个小块进行内存分配时失败的次数
        if (p->d.failed++ > 4) {
            // 如果失败的次数都>4, 那么该小块内存以后就不要再分配内存了, 更新current
            pool->current = p->d.next;
        }
    }

    p->d.next = new; // 将该小块内存尾插到内存池中

    return m;
}
```



```c
// 按大块内存来分配
static void *
ngx_palloc_large(ngx_pool_t *pool, size_t size)
{
    void              *p;
    ngx_uint_t         n;
    ngx_pool_large_t  *large;

    // 通过malloc申请size大小的大块内存
    p = ngx_alloc(size, pool->log);
    if (p == NULL) {
        return NULL;
    }

    n = 0;

    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            large->alloc = p;
            return p;
        }

        if (n++ > 3) {
            break;
        }
    }

    // 将大内存块的头部信息记录在小内存块中了
    large = ngx_palloc_small(pool, sizeof(ngx_pool_large_t), 1);
    if (large == NULL) {
        ngx_free(p);
        return NULL;
    }

    // 大内存块头部信息初始化操作
    large->alloc = p; // alloc指向了大内存块的起始位置
    // 将该大块内存头插到large中
    large->next = pool->large;
    pool->large = large;

    return p;
}
```



```c
// 通过malloc在堆上申请的内存交给nginx管理
// 比如说在内存池中有一个对象, 在外部想通过malloc申请一块资源
typedef void (*ngx_pool_cleanup_pt)(void *data); // 负责清理的回调函数
typedef struct ngx_pool_cleanup_s  ngx_pool_cleanup_t;
struct ngx_pool_cleanup_s {
    ngx_pool_cleanup_pt   handler; // 回调函数
    void                 *data; // 回调函数的参数, 即要清理的内存
    ngx_pool_cleanup_t   *next; // 下一个clean内存块
};

ngx_pool_cleanup_t *
ngx_pool_cleanup_add(ngx_pool_t *p, size_t size)
{
    ngx_pool_cleanup_t  *c;

    // 将clean内存块的头部信息记录在内存池中
    c = ngx_palloc(p, sizeof(ngx_pool_cleanup_t));
    if (c == NULL) {
        return NULL;
    }

    // 将参数信息记录在内存池中
    if (size) {
        c->data = ngx_palloc(p, size);
        if (c->data == NULL) {
            return NULL;
        }

    } else {
        c->data = NULL;
    }

    // 初始化
    c->handler = NULL;
    // 将该clean内存块头插到cleanup链表中
    c->next = p->cleanup;
    p->cleanup = c;

    ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, p->log, 0, "add cleanup: %p", c);

    return c;
}
```



#### 大内存块的释放

```c
// 对指定的大内存块进行一个free
// 对于小块内存, 由于多个小块内存可能在同一个小内存块中, 不能直接对小内存块进行释放
ngx_int_t
ngx_pfree(ngx_pool_t *pool, void *p)
{
    ngx_pool_large_t  *l;

    for (l = pool->large; l; l = l->next) {
        if (p == l->alloc) {
            ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                           "free: %p", l->alloc);
            ngx_free(l->alloc);
            l->alloc = NULL;

            return NGX_OK;
        }
    }

    return NGX_DECLINED;
}
```



#### 内存池的清空

```c
// 内存池的清空操作
void
ngx_reset_pool(ngx_pool_t *pool)
{
    ngx_pool_t        *p;
    ngx_pool_large_t  *l;

    // 将大内存块全部free掉
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            ngx_free(l->alloc);
        }
    }

    // 重置小内存块的last指针
    /*
    // nginx1.12版本, 对于last指针的重置操作不是特别合理,
    // 因为第一个小内存块的头部大小为ngx_pool_t, 但是其他小内存块的头部大小为ngx_pool_data_t
    for (p = pool; p; p = p->d.next) {
        p->d.last = (u_char *) p + sizeof(ngx_pool_t);
        p->d.failed = 0;
    }
    */
	p = pool;
	p->d.last = (u_char*)p + sizeof(ngx_pool_t);
	p->d.failed = 0;
	for (p = p->d.next; p; p = p->d.next) {
		p->d.last = (u_char*)p = sizeof(ngx_pool_data_t);
		p->d.failed = 0;
	}

    // 重置current
    pool->current = pool;
    pool->chain = NULL;
    pool->large = NULL;
}
```



#### 内存池的销毁

```c
// 内存池的销毁
void
ngx_destroy_pool(ngx_pool_t *pool)
{
    ngx_pool_t          *p, *n;
    ngx_pool_large_t    *l;
    ngx_pool_cleanup_t  *c;

    // 调用所有的clean内存块中预设的清理回调函数
    for (c = pool->cleanup; c; c = c->next) {
        if (c->handler) {
            ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                           "run cleanup: %p", c);
            c->handler(c->data);
        }
    }

#if (NGX_DEBUG)

    /*
     * we could allocate the pool->log from this pool
     * so we cannot use this log while free()ing the pool
     */

    for (l = pool->large; l; l = l->next) {
        ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0, "free: %p", l->alloc);
    }

    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                       "free: %p, unused: %uz", p, p->d.end - p->d.last);

        if (n == NULL) {
            break;
        }
    }

#endif
	// 释放所有的大内存块
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            ngx_free(l->alloc);
        }
    }
	// 释放所有的小内存块
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_free(p);

        if (n == NULL) {
            break;
        }
    }
}
```

