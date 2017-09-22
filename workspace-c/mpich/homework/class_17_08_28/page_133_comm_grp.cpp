#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int rank ,numproc ,r;
	
	int recv_buf[5] ,send_buf[5] = {1,2,3,4,5} ,send_buf2[6] = {6,7,8,9,10,11} ,recv_buf2[6];
	
	int count = 5;
	int count2 = 6;

	MPI_Init(&argc ,&argv);
	
	MPI_Group MPI_GROUP_WORLD ,group;

	MPI_Comm comm_slave ,comm_new;

	MPI_Comm comm_split;
	
    MPI_Status status;

    
	MPI_Comm_size(MPI_COMM_WORLD ,&numproc);
	MPI_Comm_rank(MPI_COMM_WORLD ,&rank);

	MPI_Comm_group(MPI_COMM_WORLD ,&MPI_GROUP_WORLD);

	int a[1] = {0};
	MPI_Group_excl(MPI_GROUP_WORLD ,1 ,a ,&group);

	MPI_Comm_create(MPI_COMM_WORLD ,group ,&comm_slave);

	if(rank != 0)
	{
		int k;
		MPI_Comm_dup(comm_slave ,&comm_new);

		MPI_Comm_compare(comm_slave ,comm_new ,&r);
		MPI_Group_rank(group ,&k);
		cout<<"The rank is "<<k<<endl;
		cout<<"myran = 0"<<", result = "<<r<<endl;
	}
	
	else
	{
		int k;
		MPI_Group_rank(group ,&k);
		cout<<"The rank is "<<k<<endl;
	}

	MPI_Finalize();
	return 0;
}