#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc ,char * argv[])
{
	int rank ,size ,i;
	int buffer[10];
	
	MPI_Status status;
	
	MPI_Init(&argc ,&argv);
	MPI_Comm_size(MPI_COMM_WORLD ,&size);
	MPI_Comm_rank(MPI_COMM_WORLD ,&rank);

	cout<<"size = "<<size<<endl;

	if(size < 2)
	{
		cout<<"Please run two processes."<<endl;
		MPI_Finalize();
		return 0;
	}

	if(rank == 0)
	{

		for(int i = 0 ;i<10 ;i++)
		{
			buffer[i] = -1;
		}

		//MPI_Barrier(MPI_COMM_WORLD);
		cout<<"proc:"<<rank<<"is gong to receive"<<endl;
		MPI_Recv(buffer ,10 ,MPI_INT ,1 ,123 ,MPI_COMM_WORLD ,&status);

		for(int i = 0 ;i<10 ;i++)
		{
			if(buffer[i] != i)
			{
				cout<<"Error:buffer["<<i<<"]="<<buffer[i]<<" but is excepted to be "<<i<<"."<<endl;
			}
		}

		for(int i = 0 ;i<10 ;i++)
		{
			cout<<rank<<": buffer["<<i<<"]="<<buffer[i]<<" ,excepted to be "<<i<<endl;
		}
	}

	if(rank == 1)
	{
		for(int i = 0 ;i<10 ;i++)
		{
			buffer[i] = i;
		}
		cout<<"proc:"<<rank<<"is gong to send"<<endl;
		MPI_Rsend(buffer ,10 ,MPI_INT ,0 ,123 ,MPI_COMM_WORLD);
		//MPI_Barrier(MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;

}