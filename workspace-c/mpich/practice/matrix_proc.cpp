#include"mpi.h"
#include<iostream>

using namespace std;

int main(int argc ,char * argv[])
{
    int rank ,numproc, a = 3,b = 2 ,c = 4;
    int matrixa[3][2] = {
        1,2,
        1,2,
        1,2,
    };
    int matrixb[2][4] = {
        1,2,3,4,
        1,2,3,4,
    };
    MPI_Status status;
    MPI_Datatype col_type ,row_type;
    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numproc);
    MPI_Type_contiguous(b ,MPI_INT ,&row_type);
    MPI_Type_vector(b ,1 ,c ,MPI_INT ,&col_type);
    MPI_Type_commit(&col_type);
    MPI_Type_commit(&row_type);

    if(rank == 0)
    {
        MPI_Send(matrixa[1] ,1 ,row_type ,1 ,1 ,MPI_COMM_WORLD);
        MPI_Send(&matrixb[0][2] ,1 ,col_type ,1 ,1 ,MPI_COMM_WORLD);
    }
    if(rank == 1)
    {
        int buf_col[2];
        int buf_row[2];
        MPI_Recv(buf_row ,1 ,row_type ,0 ,1 ,MPI_COMM_WORLD ,&status);
        MPI_Recv(buf_col ,1 ,col_type ,0 ,1 ,MPI_COMM_WORLD ,&status);
        for(int i = 0 ;i<2 ;i++)
        {
            cout<<buf_row[i]<<' ';
        }
        cout<<endl;
        for(int i = 0 ;i<2 ;i++)
        {
            cout<<buf_col[i]<<' ';
        }
        cout<<endl;
    }
}