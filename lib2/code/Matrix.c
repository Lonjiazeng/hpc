// Matrix.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void REF_MMult(int N, double* a, double* b, double* c)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                c[i * N + j] = c[i * N + j] + a[i * N + k] * b[k * N + j];
    return;
}

void init_matrix(int n, double* a, double* b, double* c)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int temp = i * n + j;
            a[temp] = temp;
            b[temp] = n * n - temp;
            c[temp] = 0;
        }
}


int main()
{
    //a、b、c用于存放矩阵变量,time1、time2用于记录时间,n是指当前为n×n矩阵，fp用于记录相关计算的运行时间
    double* a, * b, * c;
    clock_t time1;
    clock_t time2;
    int n = 1000;
    FILE* fp;
    if (!(fp = fopen("./Record.txt", "w")))
    {
        printf("打开文件失败!\n");
        return 1;
    }

    //开始测试
    while (--n > 0)
    {
        //申请动态内存
            a = (double*)malloc(sizeof(double)* (n + 1) * (n + 1));
            b = (double*)malloc(sizeof(double)* (n + 1) * (n + 1));
            c = (double*)malloc(sizeof(double)* (n + 1) * (n + 1));

            printf("N = %4d     ", n + 1);

        //初始化矩阵
            init_matrix(n+1, a, b, c);
        //开始计算并调用时间
            time1 = clock();
            REF_MMult(n+1, a, b, c);
            time2 = clock();
            printf("Start time: %20lfs      End time: %20lfs\n", (double)time1/CLOCKS_PER_SEC, (double)time2/CLOCKS_PER_SEC);
        //在文件中记录时间
            fprintf(fp, "%4d    %20lfs\n", n + 1, (double)(time2 - time1)/CLOCKS_PER_SEC);
        //释放内存空间
            free(a);
            free(b);
            free(c);
    }
    
    //关闭文件
    fclose(fp);

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
