#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void Matrix(void *arg)
{
    pthread_detach(pthread_self());
    double *Ai = *((double**)arg+1);
    double *Bj = *((double**)arg+2);
    double *Cij = *((double**)arg+3);
    int n = *((int*)arg);
    for(int k = 0; k<n;k++) 
        *Cij += *(Ai+k) * (*(Bj+k*n));
    pthread_exit(NULL);
}

int main()
{
    FILE *fp = fopen("./thread.txt","w");
    clock_t time1,time2;
    for(int n = 2;n <= 250;n++)
    {
        void **arg = (void**)malloc(sizeof(void*)*4);
        pthread_t pid[8];
        int icount = n*n;
        int i,j;
        i = j = 0;

        double *A = (double*)malloc(sizeof(double)*n*n);
        double *B = (double*)malloc(sizeof(double)*n*n);
        double *C = (double*)malloc(sizeof(double)*n*n);

        time1 = clock();
        while(icount > 0)
        {
            //调用线程
            for(int pidnum = 0;pidnum < 8;pidnum++)
            {
                icount--;
                arg[0] = (void*)&n;
                arg[1] = A + i * n;
                arg[2] = B + j;
                arg[3] = C + i * n + j;


                if(icount == 0 && pidnum < 8)
                {
                    pthread_create(pid+pidnum,NULL,(void*)&Matrix,arg);
                    pid[pidnum+1] = -1;
                    break;
                }
                else
                    pthread_create(pid+pidnum,NULL,(void*)&Matrix,arg);

                if(j == n-1)
                {
                    j = 0;
                    i++;
                }
                else
                    j++;
            }
        }
        time2 = clock();
        fprintf(fp,"%d  %lf\n",n,(double)(time2-time1)/CLOCKS_PER_SEC);
        printf("%d  %lf\n",n,(double)(time2-time1)/CLOCKS_PER_SEC);

        free(arg);
        free(A);
        free(B);
        free(C);
    }
    fclose(fp);

    return 0;
}
