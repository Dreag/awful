#include"mpi.h"
#include<iostream>

using namespace std;

void interBcast(char *buf ,int bufsize ,int rank ,int root ,int membershipKey ,MPI_Comm *comm)
{
    int i ;
    int base = 77;
    int myrank ;
    for(int i = 0 ;i<bufsize ;i++)
    {
        buf[i] = -111;
    }

    if(membershipKey == 2)
    {
        MPI_Comm_rank(MPI_COMM_WORLD ,&myrank);
        if(myrank == root)
        {
            for(int i = 0 ;i<bufsize ;i++)
            {
                buf[i] = base + i*11;
            }
            MPI_Bcast(buf ,bufsize ,MPI_INT ,MPI_ROOT ,*comm);
            for(int i = 0 ;i<bufsize ;i++)
            {
                cout<<"rank "<<rank<<" :buf["<<i<<"] = "<<buf[i]<<"is sending...."<<endl;
            }
        }
        else
        {
            MPI_Bcast(buf ,bufsize ,MPI_INT ,MPI_PROC_NULL ,*comm);
            
        }
        
    }
    else if(membershipKey == 0)
    {
        MPI_Comm_rank(MPI_COMM_WORLD ,&myrank);
        MPI_Bcast(buf ,bufsize ,MPI_INT,root ,*comm);
        cout<<"rank "<<rank<<" :buf["<<i<<"] = "<<buf[i]<<"is recieved...."<<endl;
    }
    
}
int main(int argc ,char *argv[])
{
    int rank ,numproc ,bufsize = 10;
    int membershipKey;
    char buf[10];
    MPI_Init(&argc ,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD ,&rank);
    MPI_Comm_size(MPI_COMM_WORLD ,&numproc);

    MPI_Comm myComm;
    MPI_Comm myFirstComm;
    MPI_Comm mySecondComm;
    MPI_Comm myThirdComm;
    
    membershipKey = rank%3;
    MPI_Comm_split(MPI_COMM_WORLD ,membershipKey ,rank ,&myComm);

    if(membershipKey == 0)
    {
        MPI_Intercomm_create(myComm ,0 ,MPI_COMM_WORLD ,1 , 1 ,&myFirstComm);
        MPI_Intercomm_create(myComm ,0 ,MPI_COMM_WORLD ,2 ,2 ,&myThirdComm);
    }

    else if(membershipKey == 1)
    {
        MPI_Intercomm_create(myComm ,0 ,MPI_COMM_WORLD ,0 ,1 ,&myFirstComm);
        MPI_Intercomm_create(myComm ,0 ,MPI_COMM_WORLD ,2 ,12 ,&mySecondComm);
    }

    else if(membershipKey == 2)
    {
        MPI_Intercomm_create(myComm ,0 ,MPI_COMM_WORLD ,0 ,2 ,&myThirdComm);
        MPI_Intercomm_create(myComm ,0 ,MPI_COMM_WORLD ,1 ,12 ,&mySecondComm);
    }

    interBcast(buf ,4 ,rank ,0 ,membershipKey ,&myThirdComm);

    switch (membershipKey)
    {
        case 1:
            MPI_Comm_free(&mySecondComm);
            MPI_Comm_free(&myFirstComm);
        break;
        case 0:
            MPI_Comm_free(&myFirstComm);
            MPI_Comm_free(&myThirdComm);
        break;
        case 2:
            MPI_Comm_free(&myThirdComm);
            MPI_Comm_free(&mySecondComm);
        break;
    }
    MPI_Finalize();
    
    
    
    
}
