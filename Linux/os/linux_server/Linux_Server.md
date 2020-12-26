## Linux Server

#### Linux服务器程序

* 日志系统

![image-20200930104514709](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200930104514709.png)

```shell
# 简介
rsyslogd: Linux操作系统上一个专门处理日志的守护进程
rsyslogd既能处理用户日志, 也能处理内核日志

# 工作过程
内核日志: 先将内核中的日志信息存储到内核环状缓存中, 然后直接映射到/proc/kmsg文件中
也可以通过dmesg来将内核环状缓存中的内容输出到终端
用户日志: 在用户进程中, 通过syslog()将用户日志信息输出到管道文件/dev/log中
最后守护进程rsyslogd根据配置文件信息, 将不同level的信息输出到不同的/var/log/*文件中

# 日志消息默认保存位置
内核消息: /var/log/kern.log
调试消息: /var/log/debug
普通消息: /var/log/messages
```

```c
#include <stdio.h>
#include <syslog.h>

int main() {
    // 修改打开日志方式
	openlog("gehry", LOG_PID, LOG_USER);   
    // 打日志
    syslog(LOG_INFO, "start");
    syslog(LOG_INFO, "end");
    // 关闭日志(关闭通信的管道)
    closelog();
    return 0;
}
```

![image-20200929170700074](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200929170700074.png)



* 用户信息

```shell
# 简介
用户信息是与Linux操作系统权限相关的
一个进程有2个用户id: 
1. uid (实际用户id)
2. euid (有效用户id)
同理, 一个进程也有2个用户组id: gid, egid

# 用户信息与权限之间的关系
当用户执行某个进程:
默认该进程的uid与euid都是执行该进程的用户uid
在某些情况下, 执行该进程的用户需要具备该进程文件所有者的权限, 此时就需要将该用户的uid临时修改为该进程的文件所有者id. 比如说执行su, sudo, passwd等进程时, 要读取/etc/passwd /etc/shadow等文件, 这些文件是需要root权限的

# 普通用户具备文件所有者权限的条件
该文件设置了set-user-id位, 将该进程的euid设置成文件所有者的id
这样当执行该进程时, 才能通过setuid(geteuid())来修改用户的uid为当前进程的euid
```

```c
#include <stdio.h>
#include <unistd.h>

int main() {
  int uid = getuid();
  int euid = geteuid();
  printf("uid = %d\n", uid);
  printf("euid = %d\n", euid);
  return 0;
}

// gcc main.c -o main
// sudo chown root:root main
// 设置set-user-id位: 
// sudo chmod +s main
```

![image-20201007144546538](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20201007144546538.png)

* 服务器后台化

  * 进程间关系

  ![image-20201008204322531](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20201008204322531.png)

  ![image-20201008205159045](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20201008205159045.png)

  * 守护进程

  ```shell
  # 简介
  守护进程, 就是运行在后台的脱离终端的独立进程
  所谓脱离终端其实是指脱离bash这个进程, 创建新的session并成为首领进程, 这样他就不会以来这个bash的生命周期了.
  
  # 改变工作目录与根目录
  # 改变该进程的根目录(特权进程)
  int chroot(const char *path);
  # 改变工作目录
  int chdir(const char *path);
  # 获取当前进程的工作目录, 如果>size返回null
  # 如果buf=null, 则动态开辟内存进程存储并返回该地址
  char *getcwd(char *buf, size_t size);
  ```

  ```c
  /*
  int deamon(int nochdir, int noclose)
  deamon(0, 0);
  nochdir=0: 改变工作目录为"/", 否则使用当前工作目录
  noclose=0: 将stdin,stdout,stderr定向到/dev/null文件
  */
  bool create_deamon() {
    pid_t pid = fork();                                                                                                                 
    if (pid < 0) {
      return -1;
    } else if (pid > 0) {
      // 父进程退出
      exit(1);
    } else {
      // 创建新的会话
      pid_t sid = setsid();
      if (sid < 0) {
        return false;    
      }
  
      // 切换工作目录
      if (chdir("/") < 0) {
        return false;
      }
  
      // 关闭输入输出设备, 打开的文件描述符
      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);
      // close 已经打开的文件描述符 ... 
      
      // 将输入输出定向到/dev/null文件
      umask(0); // open的文件权限为0777
      open("/dev/null", O_RDONLY);
      open("/dev/null", O_RDWR);
      open("/dev/null", O_RDWR);
      return true;
    }
  }
  ```

  ![image-20201008212348408](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20201008212348408.png)

  

  

