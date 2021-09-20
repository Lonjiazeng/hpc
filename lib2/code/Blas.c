#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    double *A,*B,*C;
    clock_t time1;
    clock_t time2;
    int n = 1000;
    FILE* fp;
    if(!(fp = fopen("./OpenBLAS_Record.txt","w")))
    {
        printf("File open Error!\n");
        return 1;
    }

    while(--n>0)
    {
        A = (double*)malloc(sizeof(double)*(n+1)*(n+1));
        B = (double*)malloc(sizeof(double)*(n+1)*(n+1));
        C = (double*)malloc(sizeof(double)*(n+1)*(n+1));

        init_matrix(n + 1, a, b, c);

        printf("N = %4d     ",n+1);


        time1 = clock();
        cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,n+1,n+1,n+1,1,A,n+1,B,n+1,1,C,n+1);
        time2 = clock();
        printf("Start time: %20lfs      End time %20lfs\n",(double)time1/CLOCKS_PER_SEC,(double)time2/CLOCKS_PER_SEC);
        fprintf(fp,"%4d     %20lfs\n",n+1,(double)(time2-time1)/CLOCKS_PER_SEC);
        free(A);
        free(B);
        free(C);
    }

    fclose(fp);
    return 0;

}


