#include"mpi.h"
#include<iostream>
#define SIZE 4

using namespace std;

int main(int argc ,char * argv[])
{
    int rank ,numproc ,tag = 1;
    
    float b[SIZE];
    float a[SIZE][SIZE] = {
        {1.0 ,1.1 ,1.2 ,1.3},
        {2.0 ,2.1 ,2.2 ,2.3},
        {3.0 ,3.1 ,3.2 ,3.3},
        {4.0 ,4.1 ,4.2 ,4.3},
    };
    
    MPI_Init(&argc ,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numproc);
    MPI_Status status;
    MPI_Datatype columntype;
    MPI_Type_vector(SIZE ,1 ,SIZE ,MPI_FLOAT ,&columntype);
    MPI_Type_commit(&columntype);
    if(numproc == SIZE)
    {
        if(rank == 0)
        {
            for(int i = 0 ;i < SIZE ;i++)
            {
                for(int j = 0 ;j < SIZE ;j++)
                {
                    cout<<a[i][j]<<' ';
                }
                cout<<endl;
            }

            for(int i = 1 ;i<SIZE ;i++)
            {
                MPI_Send(&a[0][i] ,1 ,columntype ,i ,tag ,MPI_COMM_WORLD);
            }
            
        }
        else
        {
            MPI_Recv(b ,1 ,columntype ,0 ,tag ,MPI_COMM_WORLD ,&status);
            cout<<"Process : "<<rank<<" has recev from process 0 : ";
            for(int i = 0 ;i<4; i++)
            {
                cout<<*(b + i * sizeof(float))<<' ';
            }
            cout<<endl;
        }
    }
    else
    {
        cout<<"The number of the process must be "<<SIZE<<endl;
    }
    MPI_Type_free(&columntype);
    MPI_Finalize();
}