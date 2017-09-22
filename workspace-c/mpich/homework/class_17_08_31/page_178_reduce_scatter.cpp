#include"mpi.h"
#include<iostream>

using namespace std;

int main(int arc ,char * argv[])
{
    int rank ,numprocs ,total = 0;
    char outstr[500];

    MPI_Init(&arc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numprocs);
    
    int rcnts[numprocs];
    
    for(int i = 0 ;i<numprocs ;i++)
    {
        rcnts[i] = i + 5;
        total += rcnts[i];
    }
    
    int sb[total];
    
    for(int i = 0 ;i<total ;i++)
    {
        sb[i] = i;
    }

    int rb[rcnts[rank]];
    int rb1[rcnts[rank]];

    for(int i = 0 ;i<rcnts[rank] ;i++)
    {
        rb[i] = -111;
    }

    MPI_Reduce_scatter(sb ,rb ,rcnts ,MPI_INT ,MPI_SUM ,MPI_COMM_WORLD);
   
    for(int i = 0 ;i<rcnts[rank] ;i++)
    {
        cout<<"process :"<<rank<<" reduce and get the result : "<<"rb["<<i<<"] = "<<rb[i]<<endl;
    }

    MPI_Finalize();
}