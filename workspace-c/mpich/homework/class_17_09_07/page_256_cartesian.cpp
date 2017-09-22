#include"mpi.h"
#include<iostream>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

using namespace std;

int main(int argc ,char *argv[])
{
    int rank ,numproc;
    int nbrs[4];
    int dims[2] = {4 ,4} ,periods[2] = {0 ,0};
    int coords[2];
    MPI_Init(&argc ,&argv);
    MPI_Comm_size(MPI_COMM_WORLD ,&numproc);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);

    MPI_Request reqs[8];
    MPI_Status stats[8];
    MPI_Comm cartcomm;


    if(numproc == 16)
    {
        MPI_Cart_create(MPI_COMM_WORLD ,2 ,dims ,periods ,1 ,&cartcomm);
        MPI_Comm_rank(cartcomm ,&rank);
        MPI_Cart_coords(cartcomm ,rank ,2 ,coords);
        
        MPI_Cart_shift(cartcomm ,0 ,1 ,&nbrs[UP] ,&nbrs[DOWN]);
        MPI_Cart_shift(cartcomm ,1 ,1 ,&nbrs[LEFT] ,&nbrs[RIGHT]);
        cout<<"process rank : "<<rank<<"    UP: "<<nbrs[UP]<<"    DOWN: "<<nbrs[DOWN]<<"    LEFT: "<<nbrs[LEFT]<<"    RIGHT: "<<nbrs[RIGHT]<<endl;
    }
}