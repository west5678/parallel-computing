#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

#define MASTER 0
#define n 1000000000

int main(int argc, char *argv[]){
	double x, y;
	int i;
	int count = 0;
	double z, pi = 0.0;

	MPI_Init(&argc, &argv);
	int numtasks, rank, len, rc;
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	srand(rank);


	for (i=rank; i<n; i += numtasks){
		
		x = (double)random()/RAND_MAX;
		y = (double)random()/RAND_MAX;
		z = sqrt((x*x)+(y*y));
	
		if (z <= 1)	count ++;
	}
	int total=0;
	MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 
						MASTER, MPI_COMM_WORLD);
	if (rank == MASTER){
		pi = ((double)total/n)*4.0;
		printf("number of simulation: %d \n", n);
		printf("pi: %f\n", pi);
	}
	MPI_Finalize();	
}

