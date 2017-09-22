#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int rank, numprocs;
    int matrix[5][5] = {1, 2, 3, 4, 5, 
        2, 3, 4, 5, 1,
        3, 4, 5, 1, 2, 
        4, 5, 1, 2, 3, 
        5, 1, 2, 3, 4};
    int *temp_result;   
    int **result;    //malloc if rank == 5 to save the memory.
    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numprocs);
    // MPI_Request *r;
    MPI_Status s;
    if(numprocs != 6)
    {
        cout<<"This program need 6 Process.....Terminal....."<<endl;
        
        MPI_Finalize();
        return 0;
    }

    if(rank == 5)
    {
        // s = (MPI_Status *)malloc(sizeof(MPI_Status) * 5);
        result = (int **)malloc(sizeof(int *) * 5);
        if(!result)
        {
            MPI_Abort(MPI_COMM_WORLD ,-1);
            return 0;
        }

        for(int i = 0 ;i<5 ;i++)
        {
            result[i] = (int *)malloc(sizeof(int )* 5);
            if(!result[i])
            {
                MPI_Abort(MPI_COMM_WORLD ,-1);
                return 0;
            }
        }

        for(int i = 0 ;i<5 ;i++)
        {
            MPI_Recv(result[i] ,5 ,MPI_INT ,i ,i + 1 ,MPI_COMM_WORLD ,&s);
        }

        
        for(int i = 0 ;i<5 ;i++)
        {
            for(int j = 0 ;j<5 ;j++)
            {
                cout<<result[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    
    else
    {
        temp_result = (int *)malloc(sizeof(int) * 5);
        for(int i = 0 ;i<5 ;i++)
        {
            temp_result[i] = 0;
        }

        // r = (MPI_Request *)malloc(sizeof(MPI_Request) * 5);
        for(int i = 0 ;i<5 ;i++)
        {
            for(int j = 0 ;j<5 ;j++)
            {
                temp_result[i] += matrix[rank][j] * matrix[i][j]; 

            }
        }
        // MPI_Barrier(MPI_COMM_WORLD);
        MPI_Ssend(temp_result ,5 ,MPI_INT ,5 ,rank + 1 ,MPI_COMM_WORLD); 
        
    }
    
    MPI_Finalize();

}