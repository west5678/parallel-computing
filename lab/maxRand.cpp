#include <iostream>
#include <stdlib.h>  
#include <mpi.h>

using namespace std;


int main(int argc, char ***argv){

	int rank, size, ierr;	
	float randomfraction, maxrand = 0.0;

	MPI_Init(&argc, argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand((int)(rank*(double)RAND_MAX/size));
// compute a random number
	randomfraction = (rand() / (double)RAND_MAX);
	
	MPI_Reduce(&randomfraction, &maxrand, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD);
	cout << randomfraction << endl;	
	if (rank == 0) cout << "rank::" << maxrand << endl;
	MPI_Finalize();
	return 0;
}
