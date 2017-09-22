#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int myid ,numproc ,*buf ,size = 10 ,other;
	
	MPI_Init(&argc ,&argv);
	
	MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Status status;
    MPI_Pack_size(10 ,MPI_INT ,comm ,&size);
    size += MPI_BSEND_OVERHEAD;
	MPI_Comm_size(comm ,&numproc);
	MPI_Comm_rank(comm ,&myid);
	cout<<"hello proc :"<<myid<<endl;
	if(myid == 0)
	{
		
		other = 1;
		for(int i = 0 ;i<10 ;i++)
		{
			buf[i] = i;
		}

		buf = (int *)malloc(size);
		
		MPI_Buffer_attach(buf ,10);
		cout<<"trying to send meeage to proc:" <<other<<"..."<<endl;
		MPI_Bsend(buf ,size ,MPI_INT ,other ,123 ,comm);

		
	}
	else if(myid == 1)
	{
		other = 0;
		
		MPI_Recv(buf ,size ,MPI_INT ,other ,123 ,comm ,&status);
		cout<<"recieve message from "<<other<<"..."<<endl;
		MPI_Buffer_detach(&buf ,&size);
		
		free(buf);
	}
	MPI_Finalize();
	return 0;
}