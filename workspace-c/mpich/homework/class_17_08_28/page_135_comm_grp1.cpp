#include"mpi.h"
#include<iostream>
#include<stdlib.h>

using namespace std;

int main(int argc ,char *argv[])
{
    int rank ,numprocs ,count ,count2 ,gsize ,r , size ,new_rank ,send_buf ,recv_buf;
    int ranks1[4] = {0 ,1 ,2 ,3} ,ranks2[4] = {4 ,5 ,6 ,7};
    int rnks1[8] = {0 ,1 ,2 ,3 ,4 ,5 ,6 ,7} ,rnks2[8];
    int rangein[1][3] = {{0 ,3 ,1}};
    int rangeex[1][3] = {{0 ,3 ,1}};
    char outbuf[200];
    MPI_Group orig_group ,new_group ,newgrp1 ,newgrp2 ,newgrpu ,newgrpi ,diffgrp;
    MPI_Comm new_comm;

    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&size);
    if(size != 8)
    {
        cout<<"must supcify MPI_PROCS = 8.Terminating..."<<endl;
        MPI_Finalize();
        exit(0);
    }

    send_buf = rank;

    MPI_Comm_group(MPI_COMM_WORLD ,&orig_group);

    if(rank < 4)
    {
        MPI_Group_incl(orig_group ,4 ,ranks1 ,&new_group);
    }
    else
    {
        MPI_Group_incl(orig_group ,4 ,ranks2 ,&new_group);
    }

    MPI_Comm_create(MPI_COMM_WORLD ,new_group ,&new_comm);

    MPI_Allreduce(&send_buf ,&recv_buf ,1 ,MPI_INT ,MPI_SUM ,new_comm);

    MPI_Group_rank(new_group ,&new_rank);

    MPI_Group_size(new_group ,&gsize);

    MPI_Group_compare(orig_group ,new_group ,&r);

    MPI_Group_translate_ranks(orig_group ,8 ,rnks1 ,new_group ,rnks2);

    cout<<"rank = "<<rank<<"    new rank = "<<new_rank<<"   recvbuf = "<<recv_buf<<"    gsize = "<<gsize<<"     result = "<<r<<endl;

    for(int i = 0 ;i<8 ;i++)
    {
        cout<<rnks1[i]<<"="<<rnks2[i]<<' ';
    }
    cout<<endl;
    
}