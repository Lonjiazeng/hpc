# 实验五 OpenMP并行编程

| 作者 | 龙家增        |
| ---- | ------------- |
| 时间 | 2021年10月4日 |

### OpenMP介绍（摘自维基百科）

​    **OpenMP**（Open Multi-Processing）是一套支持跨平台[共享内存](https://zh.wikipedia.org/wiki/共享内存)方式的多线程并发的编程[API](https://zh.wikipedia.org/wiki/API)，使用[C](https://zh.wikipedia.org/wiki/C),[C++](https://zh.wikipedia.org/wiki/C%2B%2B)和[Fortran](https://zh.wikipedia.org/wiki/Fortran)语言，可以在大多数的处理器体系和操作系统中运行，包括[Solaris](https://zh.wikipedia.org/wiki/Solaris), [AIX](https://zh.wikipedia.org/wiki/AIX), [HP-UX](https://zh.wikipedia.org/wiki/HP-UX), [GNU/Linux](https://zh.wikipedia.org/wiki/GNU/Linux), [Mac OS X](https://zh.wikipedia.org/wiki/Mac_OS_X), 和[Microsoft Windows](https://zh.wikipedia.org/wiki/Microsoft_Windows)。包括一套编译器指令、库和一些能够影响运行行为的环境变量。

​    OpenMP采用可移植的、可扩展的模型，为程序员提供了一个简单而灵活的开发平台，从标准桌面电脑到超级计算机的并行应用程序接口。

​    混合并行编程模型构建的应用程序可以同时使用OpenMP和[MPI](https://zh.wikipedia.org/wiki/MPI)，或更透明地通过使用OpenMP扩展的非共享内存系统上运行的计算机集群。

### OpenMP语法简介

```
#pragma omp <directive> [clause[[,] clause] ...]
```

#### directive

其中，directive共11个：

- atomic 内存位置将会原子更新（Specifies that a memory location that will be updated atomically.）
- barrier 线程在此等待，直到所有的线程都运行到此barrier。用来同步所有线程。
- critical 其后的代码块为[临界区](https://zh.wikipedia.org/wiki/临界区)，任意时刻只能被一个线程运行。
- flush 所有线程对所有共享对象具有相同的内存视图（view of memory）
- for 用在for循环之前，把for循环并行化由多个线程执行。循环变量只能是整型
- master 指定由主线程来运行接下来的程序。
- ordered 指定在接下来的代码块中，被并行化的 for循环将依序运行（sequential loop）
- parallel 代表接下来的代码块将被多个线程并行各执行一遍。
- sections 将接下来的代码块包含将被并行执行的section块。
- single 之后的程序将只会在一个线程（未必是主线程）中被执行，不会被并行执行。
- threadprivate 指定一个变量是[线程局部存储](https://zh.wikipedia.org/wiki/线程局部存储)（thread local storage）

#### clause

共计13个clause：

- copyin 让threadprivate的变量的值和主线程的值相同。
- copyprivate 不同线程中的变量在所有线程中共享。
- default Specifies the behavior of unscoped variables in a parallel region.
- firstprivate 对于线程局部存储的变量，其初值是进入并行区之前的值。
- if 判断条件，可用来决定是否要并行化。
- lastprivate 在一个循环并行执行结束后，指定变量的值为循环体在顺序最后一次执行时获取的值，或者#pragma sections在中，按文本顺序最后一个section中执行获取的值。
- nowait 忽略barrier的同步等待。
- num_threads 设置线程数量的数量。默认值为当前计算机硬件支持的最大并发数。一般就是CPU的内核数目。超线程被操作系统视为独立的CPU内核。
- ordered 使用于 for，可以在将循环并行化的时候，将程序中有标记 directive ordered 的部分依序运行。
- private 指定变量为线程局部存储。
- reduction Specifies that one or more variables that are private to each thread are the subject of a reduction operation at the end of the parallel region.
- schedule 设置for循环的并行化方法；有 dynamic、guided、runtime、static 四种方法。
  - schedule(static, chunk_size) 把chunk_size数目的循环体的执行，静态依序指定给各线程。
  - schedule(dynamic, chunk_size) 把循环体的执行按照chunk_size（缺省值为1）分为若干组（即chunk），每个等待的线程获得当前一组去执行，执行完后重新等待分配新的组。
  - schedule(guided, chunk_size) 把循环体的执行分组，分配给等待执行的线程。最初的组中的循环体执行数目较大，然后逐渐按指数方式下降到chunk_size。
  - schedule(runtime) 循环的并行化方式不在编译时静态确定，而是推迟到程序执行时动态地根据环境变量OMP_SCHEDULE 来决定要使用的方法。
- shared 指定变量为所有线程共享。

#### OpenMP的库函数

OpenMP定义了20多个库函数：

1. void omp_set_num_threads(int _Num_threads);

   在后续并行区域设置线程数，此调用只影响调用线程所遇到的同一级或内部嵌套级别的后续并行区域.说明：此函数只能在串行代码部分调用.

2. int omp_get_num_threads(void);

   返回当前线程数目.说明：如果在串行代码中调用此函数，返回值为1.

3. int omp_get_max_threads(void);

   如果在程序中此处遇到未使用 num_threads() 子句指定的活动并行区域,则返回程序的最大可用线程数量.说明：可以在串行或并行区域调用，通常这个最大数量由omp_set_num_threads()或OMP_NUM_THREADS环境变量决定.

4. int omp_get_thread_num(void);

   返回当前线程id.id从1开始顺序编号,主线程id是0.

5. int omp_get_num_procs(void);

   返回程序可用的处理器数.

6. void omp_set_dynamic(int _Dynamic_threads);

   启用或禁用可用线程数的动态调整.(缺省情况下启用动态调整.)此调用只影响调用线程所遇到的同一级或内部嵌套级别的后续并行区域.如果 _Dynamic_threads 的值为非零值,启用动态调整;否则,禁用动态调整.

7. int omp_get_dynamic(void);

   确定在程序中此处是否启用了动态线程调整.启用了动态线程调整时返回非零值;否则,返回零值.

8. int omp_in_parallel(void);

   确定线程是否在并行区域的动态范围内执行.如果在活动并行区域的动态范围内调用,则返回非零值;否则,返回零值.活动并行区域是指 IF 子句求值为 TRUE 的并行区域.

9. void omp_set_nested(int _Nested);

   启用或禁用嵌套并行操作.此调用只影响调用线程所遇到的同一级或内部嵌套级别的后续并行区域._Nested 的值为非零值时启用嵌套并行操作;否则,禁用嵌套并行操作.缺省情况下,禁用嵌套并行操作.

10. int omp_get_nested(void);

    确定在程序中此处是否启用了嵌套并行操作.启用嵌套并行操作时返回非零值;否则,返回零值.

**互斥锁操作 嵌套锁操作 功能 **

11. void omp_init_lock(omp_lock_t * _Lock); 12. void omp_init_nest_lock(omp_nest_lock_t * _Lock);

    初始化一个（嵌套）互斥锁

12. void omp_destroy_lock(omp_lock_t * _Lock); 14.void omp_destroy_nest_lock(omp_nest_lock_t * _Lock);

​	结束一个（嵌套）互斥锁的使用并释放内存.

13. void omp_set_lock(omp_lock_t * _Lock); 16.void omp_set_nest_lock(omp_nest_lock_t * _Lock);

​	获得一个（嵌套）互斥锁.

14. void omp_unset_lock(omp_lock_t * _Lock); 18.void omp_unset_nest_lock(omp_nest_lock_t * _Lock);

​	释放一个（嵌套）互斥锁.

15. int omp_test_lock(omp_lock_t * _Lock); 20.int omp_test_nest_lock(omp_nest_lock_t * _Lock);

​	试图获得一个（嵌套）互斥锁,并在成功时放回真（true）,失败是返回假（false）.

16. double omp_get_wtime(void);

​	获取wall clock time,返回一个double的数,表示从过去的某一时刻经历的时间,一般用于成对出现,进行时间比较. 此函数得到的时间是相对于线程的,也就是每一个线程都有自己的时间.

17. double omp_get_wtick(void);

​	得到clock ticks的秒数.



### 使用OpenMP并行计算矩阵乘法

本次运行环境为ubantu操作系统，CPU型号为AMD 4800U。

代码存放在lib5/code文件中，数据处理获得的结果存放在lib5/data文件夹中。将运行结果与前几次实验获得的结果进行对比，得到折线图如下：

![image-20211008152920889](C:\Users\LJZ\Desktop\image\Readme\image-20211008152920889.png)

由上图可以看到，计算速度相对于pthread有很大的提升，但是相较于单线程和OpenBLAS仍然逊色。具体原因可能如下文章所示：

[多线程为什么跑的比单线程还要慢的情况分析及验证_ljj2312的专栏-CSDN博客](https://blog.csdn.net/ljj2312/article/details/44206925)

