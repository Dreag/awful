#include"mpi.h"
#include<iostream>

using namespace std;

int main(int argc ,char * argv[])
{
    int rank ,value ,numprocs;

    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numprocs);

    do{
        if(rank == 0)
        {
            cout<<"Please input a value and the program will stop if the value is letter than 0..."<<endl;
            cin>>value;
        }
        MPI_Bcast(&value ,1 ,MPI_INT ,0,MPI_COMM_WORLD);
        cout<<"Process "<<rank<<" got "<<value<<endl;

    }
    while(value>0);

    MPI_Finalize();
    return 0;
}