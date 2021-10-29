# 实验6-1 MPI并行编程

| 姓名 | 龙家增         |
| ---- | -------------- |
| 日期 | 2021年10月22日 |

## 设计方案

​	本次实验在Ubuntu 20.04操作系统下运行，使用的处理器为AMD R7 4800U 8核心16线程。

​	本次使用8个线程，其中七个线程用于计算，主线程用于分配任务和合并数据。

 	计算A*B=C的结果时，七个线程分别处理矩阵C的不同行，若C有14行，每个处理器处理两行，为了便于计算，给出的C的规模都是7的整数倍。

主线程主要代码如下：

``````c
for(int i = 0;i < numofPro-1;i++)
        {
            MPI_Send(a+i*n*line,n*line,MPI_INT,i+1,0,MPI_COMM_WORLD);
            MPI_Send(b,n*n,MPI_INT,i+1,1,MPI_COMM_WORLD);
        }
        for(int i = 0;i < numofPro-1;i++)
        {
            MPI_Recv(buffer,line*n,MPI_INT,i+1,2,MPI_COMM_WORLD,&status);
            for(int j = 0;j<line*n;j++)
            {
                c[i*line*n] = buffer[j];
            }
        }
``````

子线程的主要代码如下：

``````c
MPI_Recv(buffer,line*n,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Recv(b,n*n,MPI_INT,0,1,MPI_COMM_WORLD,&status);

        for(int i = 0;i < line;i++)
            for(int j = 0;j < n;j++)
            {
                double temp = 0;
                for(int k = 0;k<n;k++)
                    temp += buffer[i*line + k] * b[k*n+j];
                answer[i*line+j] = temp;
            }
        
        MPI_Send(answer,line*n,MPI_INT,0,2,MPI_COMM_WORLD);
``````

代码存放在code文件夹mpi_Matrix.c文件中。

## 数据分析

详细的数据结果保存在data文件夹中

| 矩阵规模n          | 70       | 350      | 700      | 1001     |
| ------------------ | -------- | -------- | -------- | -------- |
| 串行矩阵乘法用时/s | 0.001000 | 0.108000 | 0.868000 | 2.541000 |
| MPI并行计算用时/s  | 0.000801 | 0.031588 | 0.270907 | 0.728750 |
| 加速比             | 1. 2484  | 3.4190   | 3.2041   | 3.4868   |

因为多线程运算的数据结果不准确，所以不在此进行展示。

​	可以看到，MPI多进程优化在规模较低时并不明显，但在规模较大的情况下优化性能明显。以后在使用规模较大的矩阵运算时可优先选择此方法。

