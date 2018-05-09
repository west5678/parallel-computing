#include <iostream>
#include <omp.h>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include<sys/time.h>
#include<time.h>

typedef std::vector<std::vector<float>> Array2D;

void initialize (float* x, int n){
	int n2 = n+2;
	for (int i = 0; i < n2; i++){
		for (int j = 0; j < n2; j++){
			x[i*n2+j] = ( (float)rand()/ (RAND_MAX) );
		}
	}
}

void smooth (float* y, float* x, int n, 
			float a, float b, float c){
	int j;
	for (int i=1; i<=n; i++){
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

void count(float* x, const int n, const float t, int &res){
	//the boundary is not considered
	int j;
	int n2 = n+2;
	for (int i=1; i <= n; i++){
		for (j=1; j <= n; j++){
			if (x[i*n2+j] < t){
				res ++;
			}
		}
	}
}

int main(){


	//size of matrix (nxn)
	int n = 1 << 15;
	int nbx=0, nby=0;

	//convolution constants
	float a, b, c, 
		  t,
		  *x, *y;
	a = 0.05;
	b = 0.1;
	c = 0.4;

	//threshold t
	t = 0.1;

	x = new float[(n+2)*(n+2)];
	//allocate x
	//Array2D x(n+2, std::vector<float>(n+2));

	y = new float[(n+2)*(n+2)];
	//allocate y
	//Array2D y(n+2, std::vector<float>(n+2));
	//initialize x
	initialize(x, n);	
	
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
	
	auto t1 = std::chrono::high_resolution_clock::now();	
	//smooth matrix x
	
	smooth(y, x, n, a, b, c);
	
	auto t2 = std::chrono::high_resolution_clock::now();

	auto t_cnt = std::chrono::high_resolution_clock::now();	
	  
	  count(x, n, t, nbx);
	  
	  auto t_cnt_x = std::chrono::high_resolution_clock::now();
	  
	  count(y, n, t, nby);
	  
	  auto t_cnt_y = std::chrono::system_clock::now();


	fsec t_smooth = t2 - t1;
	fsec t_count_x = t_cnt_x-t_cnt;
	fsec t_count_y = t_cnt_y-t_cnt_x;
	//count elements in first array
	//count(x, n, t, nbx);

	//count elements in second array
	//count(y, n, t, nby);


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


	std::cout << "Number of elements below threshold (X)	::" << nbx << std::endl;
	std::cout << "Fraction of elements below threshold		::" << nbx / (float)(n*n) << std::endl;
	std::cout << "Number of elements below threshold (Y)	::" << nby << std::endl;
	std::cout << "Fraction of elements below threshold		::" << nby / (float)(n*n) << std::endl;


	std::cout << "smooth time   ::" << t_smooth.count() << std::endl;
    std::cout << "count-x time  ::" << t_count_x.count() << std::endl;
    std::cout << "count-y time  ::" << t_count_y.count() << std::endl;
	return 0;
}
