# 实验4：Linux环境多线程编程

| 完成人 | 龙家增        |
| ------ | ------------- |
| 时间   | 2021年9月27日 |



基于实验3实现的多线程HTTP	server代码已存放在code文件夹下的[thread_server.c](https://github.com/Lonjiazeng/hpc/blob/main/lib4/code/thread_server.c)文件中



## 多线程矩阵乘法

有关代码存放在code文件夹下[Matrix.c](https://github.com/Lonjiazeng/hpc/blob/main/lib4/code/Matrix.c)

#### 设计思路

​	根据矩阵乘法的定义，将矩阵乘法C = AB中A矩阵按行划分、B按列划分，得到类似结果如下图

![image-20211006180619870](https://github.com/Lonjiazeng/hpc/blob/main/lib4/image/Readme/62180FE1BFFC803077772EDB70DCEF48.png)

其中
$$
C_{ij} = A_iB_{j}
$$
调用线程完成每一个小步计算，本次计算使用的CPU是`AMD 锐龙 4800U`,8核心16线程，所以将设计最大线程为16。

#### 函数设计

​	线程调用函数为`void Matrix(void *arg)`,其中参数arg为一个数组指针，一共有四个元素，第一个指向元素p，第二个指向Ai的第一个元素，第三个指向Bj的第一个元素，第四个指向Cij。具体如下图：

<img src="https://github.com/Lonjiazeng/hpc/blob/main/lib4/image/Readme/62180FE1BFFC803077772EDB70DCEF48.png" alt="62180FE1BFFC803077772EDB70DCEF48" style="zoom: 25%;" />

函数完成Ai与Bj的计算后将结果保存在Cij里，然后退出。

#### 实验数据与之前实验结果的比较

​	编译代码`gcc  Thread_Matrix.c -o Thread_Matrix` ,完成后运行`./Thread_Matrix`报错“段错误（核心）已转储”，网上查有关错误进行一一排除：

+ 栈溢出——使用`ulimit -s 102400`增加栈容量，没有效果
+ 数组越界操作——检查后没有发现

+ 更换到Windows平台使用vs2022Preview配置相关环境后启用调式模式运行，在没有设置断点的情况下报错”到达了一个断点“并出现新页面“未加载 wntdll.pdb"。尝试直接编译后运行，报错“程序无法正常启动（0xc000007b）”。尝试无果返回ubantu系统。

+ 尝试降低调用线程，由16线程改为8线程，使用前述命令编译并运行，无法运行，报错”段错误（核心）已转储”。

+ 在降低调用线程的情况下降低n（矩阵规模）值，由1000降到400，调用上述命令，正常运行，运行结果保存至[threadn.txt]()文件。

将其结果与之前实验结果对比，得到折线图如下：

​    ![image-20211007111229186](https://github.com/Lonjiazeng/hpc/blob/main/lib4/image/Readme/image-20211007111229186.png)

检查运行结果时发现运行时间过大，在网络上查询，调用`./Thread_Matrix 10`，报错**“段错误（核心）已转储”**，将n更改为250，更改命令`./Thread_Matrix 8`,正常运行，结果保存至[thread.txt](),更新结果如下：

![image-20211007111746773](https://github.com/Lonjiazeng/hpc/blob/main/lib4/image/Readme/image-20211007111746773.png)

性能有小幅改善，但仍然低于普通矩阵乘法和OpenBLAS库方法。

推测代码出现问题，受限于个人水平无法查出。
