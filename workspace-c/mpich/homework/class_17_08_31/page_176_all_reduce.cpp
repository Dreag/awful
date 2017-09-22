#include"mpi.h"
#include<iostream>

using namespace std;

int main(int argc ,char * argv[])
{
    int rank ,numprocs ,size = 5 ,send_buf[size] ,recv_buf;

    for(int i = 0 ;i<size ;i++)
    {
        send_buf[i] = i + 1;
    }
    MPI_Init(&argc ,&argv);
    MPI_Barrier(MPI_COMM_WORLD);
    double elapsed_time = - MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numprocs);
    MPI_Allreduce(send_buf ,&recv_buf ,size ,MPI_INT ,MPI_PROD ,MPI_COMM_WORLD);
    
    cout<<"process : "<<rank<<" has the value of recv_buf :"<<recv_buf<<","<<*(&recv_buf + 1)<<endl;
    elapsed_time += MPI_Wtime();
    MPI_Finalize();
    cout<<"Time spend"<<elapsed_time;
    return 0;
}
