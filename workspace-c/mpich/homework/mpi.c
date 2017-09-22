#include "mpi.h"
#include <stdio.h>

void interBcast(int *buf, int bufsize, int rank, int root, int membershipKey, MPI_Comm *comm)
{
	int i;
	
	int base=77;
	int myrank;
	char printb[200];
	//MPI_COMM_WORLD中rank=8的进程在mythirdcomm中rank=2

	for(i=0;i<bufsize;i++)
	{
		buf[i]=-111;
	}
	if(membershipKey==2){
		MPI_Comm_rank(*comm,&myrank);
		if(myrank==root){
			for(i=0;i<bufsize;i++){
				buf[i]=base+i*11;
			}
		}
	}