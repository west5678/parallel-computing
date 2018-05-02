#include <iostream>
#include <omp.h>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include<sys/time.h>
#include<time.h>
#include "mpi.h"
#include <stdio.h>

#define MASTER 0


typedef std::vector<std::vector<float>> Array2D;

void initialize (float* x, int n, int numtasks){
	int n2 = n+2;
	int m = n/numtasks + 2;
	for (int i = 0; i < n+2*numtasks; i++){
		if (i>1 && (i%m == 0 || i%m == m-1)){
			for (int j = 0; j < n2; j++){
				x[i*n2+j] = x[(i-2)*n2+j];
			}
		}



		for (int j = 0; j < n2; j++){
			x[i*n2+j] = ( (float)rand()/ (RAND_MAX) );
		}
	}
}

void smooth (float* y, float* x, int m, int n, 
			float a, float b, float c){
	int j;
	for (int i=1; i<=m; i++){
		for (j=1; j<=n; j++){
			y[i*(n+2) + j] = a * (x[(i-1)*(n+2)+(j-1)] + 
								x[(i-1)*(n+2)+(j+1)] + 
								x[(i+1)*(n+2)+(j-1)] + 
								x[(i+1)*(n+2)+(j+1)])
						+ b * (x[(i-1)*(n+2)+j] + 
								x[(i+1)*(n+2)+j] + 
								x[i*(n+2)+(j-1)] + 
								x[i*(n+2)+(j+1)]) 
						+ c * x[i*(n+2)+j];
		}
	}
}

void count(float* x, const int m, const int n, 
			const float t, int &res){
	//the boundary is not considered
	int j;
	int n2 = n+2;
	for (int i=1; i <= m; i++){
		for (j=1; j <= n; j++){
			if (x[i*n2+j] < t){
				res ++;
			}
		}
	}
}

int main(int argc, char *argv[]){

    MPI_Init(&argc, &argv);
	int numtasks, rank, len, rc;
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("This is task %d\n", rank);

	//size of matrix (nxn)
	int n = 1 << 15;
	int nbx=0, nby=0;

	//convolution constants
	float a, b, c, 
		  t,
		  *x, *y, *x_pe, *y_pe;
	a = 0.05;
	b = 0.1;
	c = 0.4;

	//threshold t
	t = 0.1;
	if (rank == 0){
		x = new float[(n+2*numtasks)*(n+2*numtasks)];
		//allocate x

		y = new float[(n+2*numtasks)*(n+2*numtasks)];
		//allocate y
		//initialize x
		initialize(x, n, numtasks);	
	}
	x_pe = new float[(n/numtasks+2)*(n+2)];
	y_pe = new float[(n/numtasks+2)*(n+2)];

	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;

	auto t1 = std::chrono::high_resolution_clock::now();	
	//smooth matrix x
	MPI_Scatter(x, (n/numtasks+2)*(n+2), MPI_FLOAT, 
				x_pe, (n/numtasks+2)*(n+2), MPI_FLOAT, 0, MPI_COMM_WORLD);
	
	smooth(y_pe, x_pe, n/numtasks, n, a, b, c);
	
	auto t2 = std::chrono::high_resolution_clock::now();

	auto t_cnt = std::chrono::high_resolution_clock::now();	
	//count X  
	int cnt_x = 0;
	count(x_pe, n/numtasks, n, t, nbx);
	MPI_Reduce(&nbx, &cnt_x, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
	  
	auto t_cnt_x = std::chrono::high_resolution_clock::now();
	//count Y
	count(y_pe, n/numtasks, n, t, nby);
	
	int cnt_y=0;
	MPI_Reduce(&nby, &cnt_y, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
	  
	auto t_cnt_y = std::chrono::system_clock::now();


	fsec t_smooth = t2 - t1;
	fsec t_count_x = t_cnt_x-t_cnt;
	fsec t_count_y = t_cnt_y-t_cnt_x;
	


	if (rank==0){
	//Formatted Output
		std::cout << std::endl;
		std::cout << "Summary" << std::endl;
		std::cout << "-------" << std::endl;
		std::cout << "Number of elements in a row/column		::" << n+2 << std::endl;
		std::cout << "Number of inner elements in a row/column	::" << n << std::endl;
		std::cout << "Total number of elements					::" << (n+2)*(n+2) << std::endl;
		std::cout << "Total number of inner elements			::" << n*n << std::endl;
		std::cout << "Memory (GB) used per array				::" << (n+2)*(n+2)*sizeof(float)/float(1024*1024*1024) << std::endl;
		std::cout << "Threshold									::" << t << std::endl;
		std::cout << "Smoothing constants (a, b, c)				::" << a << " " << b << " " << c << std::endl;


		std::cout << "Number of elements below threshold (X)	::" << cnt_x << std::endl;
		std::cout << "Fraction of elements below threshold		::" << cnt_x / (float)(n*n) << std::endl;
		std::cout << "Number of elements below threshold (Y)	::" << cnt_y << std::endl;
		std::cout << "Fraction of elements below threshold		::" << cnt_y / (float)(n*n) << std::endl;

		std::cout << "Number of Processes	::" << numtasks << std::endl;
		std::cout << "smooth time   ::" << t_smooth.count() << std::endl;
    	std::cout << "count-x time  ::" << t_count_x.count() << std::endl;
    	std::cout << "count-y time  ::" << t_count_y.count() << std::endl;
	}
	MPI_Finalize();
	return 0;
}
