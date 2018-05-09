#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

#define MASTER 0
#define n 1000000

int main(int argc, char *argv[]){
	int i;
	double x2, d2 = 1.0/n;	
	double pi, result=0.0, sum=0.0;

	MPI_Init(&argc, &argv);
	int numtasks, rank, len, rc;
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	srand(rank);

	for (i=rank; i<n; i += numtasks){
		x2 = d2*i*d2*i;
		result += sqrt(1-x2);
	}

	MPI_Reduce(&result, &sum, 1, MPI_DOUBLE, MPI_SUM, 
						MASTER, MPI_COMM_WORLD);
	if (rank == MASTER){
		pi = sum*4.0/n;
		printf("number of steps: %d \n", n);
		printf("d: %f\n", d2);
		printf("pi: %f\n", pi);
	}
	MPI_Finalize();	
}

