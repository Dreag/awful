#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int rank ,numproc ,index ,a = 0 ,buf[100];
	

	MPI_Init(&argc ,&argv);
	
	MPI_Request reqlist[100];

	MPI_Request req;
	MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Status status;

	MPI_Comm_size(comm ,&numproc);
	MPI_Comm_rank(comm ,&rank);

	if(rank >0 )
	{
		while(true) {
			a++;
		    MPI_Isend(&a ,1 ,MPI_INT ,1 ,1 ,comm ,&reqlist[a]);
		   cout<<"send "<<a<<" by isend."<<endl;
		}
	}
	else
	{
		for(int i = 0 ;i<100 ;i++)
		{
			MPI_Irecv(&buf[i] ,1 ,MPI_INT ,0 ,1 ,comm ,&reqlist[i]);
		}
		while(true) {
		    MPI_Waitany(100 ,reqlist ,&index ,&status);
		    cout<<"the number:"<<index<<" is recieved .The data is "<<buf[index]<<endl;
		   // MPI_Irecv(buf ,size ,MPI_TYPE ,dest ,tag ,comm ,&req);
		}
	}

	MPI_Finalize();
	return 0;
}