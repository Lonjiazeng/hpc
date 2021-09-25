#  **实验三**

##  进程知识总结

**就绪状态：** 当进程已分配到除CPU以外的所有必要资源后，只要再获得CPU，便可立即执行，这种状态称为就绪状态；

**执行状态：** 进程已获得CPU，其程序正在执行；

**阻塞状态：** 正在执行的进程由于发生某事件而暂时无法继续执行时，便放弃CPU而处于暂停状态，亦即进程的执行受到阻塞，把这种暂停状态称为阻塞状态，有时也称为等待状态或封锁状态。比如进程当中调用wait()函数，会使得进程进入到阻塞状态。

**挂起状态：** 在不少系统中进程只有上述三种状态，但在另一些系统中，又增加了一些新状态，最重要的是挂起状态。引入挂起状态的原因有：

(1) 终端用户的请求。当终端用户在自己的程序运行期间发现有可疑问题时，希望暂时使自己的程序静止下来。

(2) 父进程请求。有时父进程希望挂起自己的某个子进程，以便考查和修改该子进程，或者协调各子进程间的活动。

(3) 负荷调节的需要。当实时系统中的工作负荷较重，已可能影响到对实时任务的控制时，可由系统把一些不重要的进程挂起，以保证系统能正常运行。

(4) 操作系统的需要。操作系统有时希望挂起某些进程，以便检查运行中的资源使用情况或进行记账。

**创建状态：** 为一个新进程创建PCB（进程控制块，它是系统为了管理进程设置的一个专门的数据结构，主要表示进程的状态），把该进程转入到就绪状态并插入到就绪队列之中。

**终止状态：** 等待操作系统进行善后处理，然后将其PCB清零，并将PCB空间返还系统。

**五种状态的转换关系图：**

![img](https://github.com/Lonjiazeng/hpc/blob/main/lib3/v2-c07a9c44b018409433a427a29e417599_720w.jpg)



##  进程控制函数 

| 函数                                                      | 说明                                |
| :-------------------------------------------------------- | ----------------------------------- |
| [atexit()](http://c.biancheng.net/cpp/html/270.html)      | 设置程序正常结束前调用的函数        |
| [execl()](http://c.biancheng.net/cpp/html/271.html)       | 执行文件函数                        |
| [execlp()](http://c.biancheng.net/cpp/html/272.html)      | 从PATH 环境变量中查找文件并执行     |
| [execv()](http://c.biancheng.net/cpp/html/273.html)       | 执行文件函数                        |
| [execve()](http://c.biancheng.net/cpp/html/274.html)      | 执行文件函数                        |
| [execvp()](http://c.biancheng.net/cpp/html/275.html)      | 执行文件函数                        |
| [exit()](http://c.biancheng.net/cpp/html/276.html)        | 结束进程                            |
| [_exit()](http://c.biancheng.net/cpp/html/277.html)       | 结束进程执行                        |
| [getpgid()](http://c.biancheng.net/cpp/html/278.html)     | 获取进程组识别码                    |
| [getpgrp()](http://c.biancheng.net/cpp/html/279.html)     | 获取进程组识别码                    |
| [getpid()](http://c.biancheng.net/cpp/html/280.html)      | 获取进程识别码                      |
| [getppid()](http://c.biancheng.net/cpp/html/281.html)     | 取得父进程的进程识别码              |
| [getpriority()](http://c.biancheng.net/cpp/html/282.html) | 取得程序进程执行优先权              |
| [nice()](http://c.biancheng.net/cpp/html/283.html)        | 改变进程优先顺序                    |
| [on_exit()](http://c.biancheng.net/cpp/html/284.html)     | 设置程序正常结束前调用的函数        |
| [setpgid()](http://c.biancheng.net/cpp/html/285.html)     | 设置进程组识别码函数                |
| [setpgrp()](http://c.biancheng.net/cpp/html/286.html)     | 设置进程组识别码                    |
| [setpriority()](http://c.biancheng.net/cpp/html/287.html) | 设置程序进程执行优先权              |
| [system()](http://c.biancheng.net/cpp/html/288.html)      | 执行shell命令                       |
| [wait()](http://c.biancheng.net/cpp/html/289.html)        | 结束(中断)进程函数(常用)            |
| [waitpid()](http://c.biancheng.net/cpp/html/290.html)     | 中断(结束)进程函数(等待子进程中断或 |
| [fprintf()](http://c.biancheng.net/cpp/html/291.html)     | 输出函数(格式化输出数据至文件)      |
| [fscanf()](http://c.biancheng.net/cpp/html/292.html)      | 输入函数(比较常用)                  |
| [sacnf()](http://c.biancheng.net/cpp/html/294.html)       | 字符串输入函数(最常用的输入函数)    |
| [vfprintf()](http://c.biancheng.net/cpp/html/297.html)    | 输出函数(格式化输出数据至文件)      |
| [vfscanf()](http://c.biancheng.net/cpp/html/298.html)     | 输入函数(先格式化字符串再输入)      |
| [vprintf()](http://c.biancheng.net/cpp/html/299.html)     | 输出函数                            |
| [vscanf()](http://c.biancheng.net/cpp/html/300.html)      | 字符串格式化输入函数                |
| [vsprintf()](http://c.biancheng.net/cpp/html/301.html)    | 格式化字符串                        |
| [vsscanf()](http://c.biancheng.net/cpp/html/302.html)     | 字符串输入函数                      |
| [vfork()](http://c.biancheng.net/cpp/html/1141.html)      | 建立新的进程                        |

[参考链接1](https://zhuanlan.zhihu.com/p/77118122)

[参考链接2](https://www.cnblogs.com/king-77024128/articles/2684317.html)

[参考链接3](http://c.biancheng.net/cpp/u/hs7/)

## 多进程

代码放在code文件夹中
