#include <iostream>
#include <stdio.h>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]){
	MPI_Comm comm=MPI_COMM_WORLD;
	MPI_Status status;
	MPI_Request reqs;
	int nranks,rank=-1,ierr; 
	int irec=-1.0;

	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_size(comm,&nranks);
	ierr=MPI_Comm_rank(comm, &rank ); 
	
	for(int j = 0; j < 8; j++){
		if(j==rank) continue;
		MPI_Isend(&rank, 1, MPI_INT, j, rank, comm, &reqs);
	}

	for(int j = 0; j < 8; j++){
		if(j==rank) continue;
		MPI_Recv(&irec, 1, MPI_INT, j, j, comm, &status);
		printf("rank %d received message from rank %d \n", rank, irec);
	}
	ierr=MPI_Finalize(); 

}	
