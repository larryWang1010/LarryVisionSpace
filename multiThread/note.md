# 绑定进程到某个CPU核心
有很多方法可以实现将某个进程绑定在某个cpu核心上
1. shell命令

```sh
# 启动程序xxx时绑定到cpu 1 核心上
$taskset -c 1 ./xxx&
# 确认，查看进程当前运行在哪个cpu上
$task -p pid_num
```

2. 使用
`sched_setaffinity`可以将某个进程绑定到一个特定的CPU
```c++
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>

/* 设置进程号为pid的进程运行在mask所设定的CPU上
 * 第二个参数cpusetsize是mask所指定的数的长度
 * 通常设定为sizeof(cpu_set_t)

 * 如果pid的值为0,则表示指定的是当前进程 
 */
int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);

int sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);/* 获得pid所指示的进程的CPU位掩码,并将该掩码返回到mask所指向的结构中 */
```
# 绑定线程都某个cpu核心
绑定线程到cpu核上运行
绑定线程到cpu核上使用pthread_setaffinity_np函数，其原型定义如下：
```c++
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <pthread.h>

int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize, const cpu_set_t *cpuset);
int pthread_getaffinity_np(pthread_t thread, size_t cpusetsize, cpu_set_t *cpuset);

Compile and link with -pthread.
```

# 查看内存和cpu占用率
查看某个进程的实时cpu以及内存占用率


```sh
$top -p 2913

top - 17:34:39 up  6:31,  2 users,  load average: 3.62, 3.25, 2.52
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
%Cpu(s): 15.8 us,  4.1 sy,  0.0 ni, 76.5 id,  3.5 wa,  0.0 hi,  0.0 si,  0.0 st
MiB Mem :  15696.1 total,   3701.0 free,   8149.1 used,   3846.0 buff/cache
MiB Swap:   2048.0 total,    783.5 free,   1264.5 used.   6819.7 avail Mem 

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                          
  66516 larry     20   0 2604936 681904  70600 S 202.3   4.2   6:34.61 stereo_euroc 
```


  

参考
https://blog.csdn.net/guotianqing/article/details/80958281