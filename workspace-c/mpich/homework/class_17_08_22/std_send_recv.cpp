

#include "mpi.h"
#include <iostream>
#include <math.h>

using namespace std;

#define buf_size 10

int main(int argc,char *argv[])
{
    int n ,myid ,numprocs ,other ,sb[buf_size] ,rb[buf_size] ,namelen;
    MPI_Status status;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    
    for(int i = 0 ;i<buf_size ;i++)
    {
        sb[i] = myid + i;
    }

    if(myid == 0)
    {
        other = 1;
    }

    if(myid == 1)
    {
        other = 0;
    }

    if(myid == 0)
    {
        cout<<"process :"<<myid<<" of "<<numprocs<<" trying sending..."<<endl;
        
        MPI_Send(sb ,buf_size ,MPI_INT ,other ,1 ,MPI_COMM_WORLD);

        cout<<"process :"<<myid<<" of "<<numprocs<<"trying receiving..."<<endl;

        MPI_Recv(rb ,buf_size ,MPI_INT ,other ,1 ,MPI_COMM_WORLD ,&status);
    }
    
    if(myid == 1)
    {
        cout<<"process :"<<myid<<" of "<<numprocs<<" trying sending..."<<endl;
        
        MPI_Recv(rb ,buf_size ,MPI_INT ,other ,1 ,MPI_COMM_WORLD ,&status);

        cout<<"process :"<<myid<<" of "<<numprocs<<"trying receiving..."<<endl;

        MPI_Send(sb ,buf_size ,MPI_INT ,other ,1 ,MPI_COMM_WORLD);

    }

    cout<<"Hello world! Process "<<myid<<" of "<<numprocs<<endl;
  	
    MPI_Finalize();

    return 0;
}
