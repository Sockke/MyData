#include <stdio.h>
#include <unistd.h>

/*
  fork之后, 子进程拷贝父进程的文件描述符表,
  共享文件表表项, 因此指向文件的位置也是共享的

  共享文件:
  1. 在内核中, 打开文件的信息由3个数据结构来进行组织,
  分别是文件描述符表, 文件表, vnode表
  2. 文件描述符表, 每个进程都有一份独立的文件描述符表,
  记录了打开的文件描述符, 以及对应的文件表表项.
  3. 文件表, 文件表表项记录了打开文件的信息, 包括文件指针的位置, 引用计数,
  以及vnode表项, 所有进程共享
  4. vnode表, 记录了文件的具体信息(文件类型, 文件大小等具体信息)
  所有进程共享

*/

#if 0
int main() {
  fork() || fork();  // 子进程返回0
  printf("A\n");
  return 0;
}
#endif
