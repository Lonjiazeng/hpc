#include <stdio.h>
#include <stdlib.h>
#include <mpich/mpi.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int myid,numofPro;
    int x = 10;
    int n = 7*x;
    MPI_Status status;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numofPro);
    int line = n/(numofPro-1);


    if(myid == 0)
    {
        double *a = (double*)malloc(sizeof(double)*n*n);
        double *b = (double*)malloc(sizeof(double)*n*n);
        double *c = (double*)malloc(sizeof(double)*n*n);
        double *buffer = (double*)malloc(sizeof(double)*line*n);
        clock_t start,end;
        FILE *P = fopen("./MPI_Matrix.txt","a+");

        start = clock();
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
        end = clock();
        fprintf(P,"%d     %lf\n",n,((double)(end-start))/CLOCKS_PER_SEC);
        printf("%d     %lf\n",n,((double)(end-start))/CLOCKS_PER_SEC);

        free(a);
        free(b);
        free(c);
        free(buffer);
        fclose(P);
    }
    else
    {
        double *b = (double*)malloc(sizeof(double)*n*n);
        double *buffer = (double*)malloc(sizeof(double)*line*n);
        double *answer = (double*)malloc(sizeof(double)*line*n);

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

        free(buffer);
        free(b);
        free(answer);
            
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}