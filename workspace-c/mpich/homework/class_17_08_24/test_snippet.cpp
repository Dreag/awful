#include "mpi.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	int myid ,numproc ,*buf;
	
	MPI_Init(&argc ,&argv);
	
	MPI_Comm comm = MPI_COMM_WORLD;

	MPI_Status status;

	MPI_Comm_size(comm ,&myid);
	MPI_Comm_rank(comm ,&numproc);

	MPI_Finalize();
	if(myid == 0)
	{

		int size = 10;
		for(int i = 0 ;i<10 ;i++)
		{
			buf[i] = i;
		}
		

		buf = (int *)malloc(size);
		
		MPI_Buffer_attach(buf ,size);
		
		MPI_Bsend(buf ,10 ,MPI_INT ,1 ,1 ,comm);
		
		
	}

	else if(myid == 1)
	{
		MPI_Recv(buf ,10 ,MPI_INT ,0 ,1 ,comm ,&status);
		int i = 10;
		MPI_Buffer_detach(&buf ,&i);
		free(buf);
	}
	
	return 0;
}