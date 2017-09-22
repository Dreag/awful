#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int myid ;
	char buf[10];
	
	for(int i = 0 ;i<10 ;i++)
	{
		buf[i] = i + '0';
	}
	buf[9] = '\0';

	MPI_Init(&argc ,&argv);
	MPI_Status status;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm ,&myid);

	if(myid == 0)
	{
		MPI_Recv(buf ,10 ,MPI_CHAR ,1 ,0 ,comm ,&status);
		cout<<myid<<" recv message:"<<buf<<endl;
		MPI_Send(buf ,10 ,MPI_CHAR ,1 ,0 ,comm);
		cout<<myid<<" is trying to send message"<<endl;
	}

	else if(myid == 1)
	{
		MPI_Recv(buf ,10 ,MPI_CHAR ,0 ,0 ,comm ,&status);
		cout<<myid<<" recv message:"<<buf<<endl;	
		MPI_Send(buf ,10 ,MPI_CHAR ,0 ,0 ,comm);
		cout<<myid<<" is trying to send message"<<endl;
	
	}

	MPI_Finalize();
	return 0;
}