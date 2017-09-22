#include"mpi.h"
#include<iostream>
#define CART_DIM 2
#define GRAPH_NEIBS 2

using namespace std;


int main(int argc ,char *argv[])
{
    int dims[CART_DIM] ,periods[CART_DIM] ,numproc ,rank;
    int outdims[CART_DIM] ,outperiods[CART_DIM] ,outcoords[CART_DIM];
    int topo_type;
    int *index ,*edge ,*outindex ,*outedges;
    MPI_Comm comm1 ,comm2;

    MPI_Init(&argc ,&argv);
    MPI_Comm_size(MPI_COMM_WORLD ,&numproc);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);

    dims[0] = dims[1] = 0;
    MPI_Dims_create(numproc ,CART_DIM ,dims);
    periods[0] = periods[1] = 0;

    MPI_Cart_create(MPI_COMM_WORLD ,2 ,dims ,periods ,0 ,&comm1);
    MPI_Comm_dup(comm1 ,&comm2);
    
    
    
}