#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int rank ,numproc ,rba[1] ,rbb[1] ,sba[1] ,sbb[1];
	sba[0] = 1;
	sbb[0] = 2;
	MPI_Init(&argc ,&argv);
	MPI_Request req;
	
	MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Status status;

	MPI_Comm_size(comm ,&numproc);
	MPI_Comm_rank(comm ,&rank);

	

	if(rank == 0)
	{
		cout<<"trying to send "<<sba[0]<<" with ssend to dest:1"<<endl;
		MPI_Ssend(sba ,1 ,MPI_INT ,1 ,0 ,comm);
		cout<<"trying to send "<<sbb[0]<<" with send to dest:1"<<endl;
		MPI_Send(sbb ,1 ,MPI_INT ,1 ,1 ,comm);
	}
	else
	{
		MPI_Irecv(rba ,1 ,MPI_INT ,0 ,0 ,comm ,&req);

		MPI_Recv(rbb ,1 ,MPI_INT ,0 ,1 ,comm ,&status);
		cout<<"recive "<<rbb[0]<<" from sender:0"<<endl;
		MPI_Wait(&req ,&status);
		cout<<"recive "<<rba[0]<<" from sender:0"<<endl;
		
	}


	MPI_Finalize();
	return 0;
}