#include"mpi.h"
#include<iostream>

using namespace std;

static int BUF_SIZE = 5;

int main(int argc ,char * argv[])
{
    int rank ,numprocs ,sb[BUF_SIZE] ,rb[BUF_SIZE];
    
    char outstr[500];

    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numprocs);

    cout<<"Process :"<<rank<<" start scan...."<<endl;
    for(int i = 0 ;i<BUF_SIZE ;i++)
    {
        sb[i] = rank* numprocs + i;
        cout<<"process : "<<rank<<" sb["<<i<<"] = "<<sb[i]<<endl;
    }
    
    cout<<"before scan...."<<endl;
    MPI_Scan(sb ,rb ,BUF_SIZE ,MPI_INT ,MPI_SUM ,MPI_COMM_WORLD);
    cout<<"after scan...."<<endl;

    for(int i = 0 ;i<BUF_SIZE ;i++)
    {
        cout<<"process : "<<rank<<" rb["<<i<<"] = "<<rb[i]<<endl;
    }

    MPI_Finalize();
}