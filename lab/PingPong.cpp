#include <stdio.h>
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]){
	MPI_Comm comm=MPI_COMM_WORLD;
	MPI_Status status;
	int nranks,rank=-1,ierr; 
	int irec=-1.0;

	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_size(comm,&nranks);
	ierr=MPI_Comm_rank(comm, &rank ); 
	
	if (rank==0){
		MPI_Send(&rank, 1, MPI_INT, 1, 9, comm);
		MPI_Recv(&irec, 1, MPI_INT, 1, 9, comm, &status);
	}
	else if(rank==1){
		MPI_Send(&rank, 1, MPI_INT, 0, 9, comm);
		MPI_Recv(&irec, 1, MPI_INT, 0, 9, comm, &status);
	}
		
	printf("rank %d received message from rank %d \n", rank, irec);

	ierr=MPI_Finalize(); 

}	
