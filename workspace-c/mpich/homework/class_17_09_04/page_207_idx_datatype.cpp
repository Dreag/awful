#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int rank, numproc, tag;
    int blocklengths[2];
    int displacements[2];
    float a[16];
    float b[16];
    for (int i = 1; i <= 16; i++)
    {
        a[i - 1] = (float)i;
    }

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numproc);
    MPI_Comm_rank(MPI _COMM_WORLD, &rank);

    MPI_Status status;

    MPI_Datatype indextype;

    blocklengths[0] = 4;
    blocklengths[1] = 2;
    displacements[0] = 5;
    displacements[1] = 12;

    MPI_Type_indexed(2, blocklengths, displacements, MPI_FLOAT, &indextype);
    MPI_Type_commit(&indextype);

    if (rank == 0)
    {
        for (int i = 1; i < numproc; i++)
        {
            MPI_Send(a, 1, indextype, i, tag, MPI_COMM_WORLD);
        }
    }
    else
    {
        for (int i = 0; i < 16; i++)
        {
            b[i] = -1.0;
        }
        MPI_Recv(b, 1, indextype, 0, tag, MPI_COMM_WORLD, &status);
        cout << "Process : " << rank << " has recev from process 0 : ";
        for (int i = 0; i < 16; i++)
        {
            cout << b[i] << ' ';
        }
        cout << endl;

        MPI_Type_free(&indextype);
        MPI_Finalize();
    }
}