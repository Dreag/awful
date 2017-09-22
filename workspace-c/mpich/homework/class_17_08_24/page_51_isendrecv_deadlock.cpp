#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int rank ,numproc ,size = 10 ,buf[10];
	
	MPI_Init(&argc ,&argv);
	
	MPI_Comm comm = MPI_COMM_WORLD;

	MPI_Request req;

    MPI_Status status;

	MPI_Comm_size(comm ,&numproc);
	MPI_Comm_rank(comm ,&rank);

	if(rank == 0)
	{
		for(int i = 0 ;i<size ;i++)
		{
			buf[i] = i;
		}

		MPI_Recv(buf ,size ,MPI_INT ,1 ,1 ,comm ,&status);
		cout<<"recieve an array from 1"<<endl;
		
		MPI_Isend(buf ,size ,MPI_INT ,1 ,1 ,comm ,&req);
		cout<<"send an array to 1"<<endl;

	}

	else if(rank == 1)
	{
		for(int i = 0 ;i<size ;i++)
		{
			buf[i] = i + 1;
		}
		//MPI_Isend(buf ,size ,MPI_INT ,0 ,1 ,comm ,&req);
		//cout<<"send an array to 1"<<endl;
		

	}
	MPI_Finalize();

	return 0;
}