#include <iostream>
#include <omp.h>
#include <vector>
#include <stdlib.h>

#include<sys/time.h>
#include<time.h>


//timer class
class Timer
{
	public:
		Timer(): n(0) { }
		void start(std::string label)
		{
			if (n < 20)
			{ labels[n] = label; times[2*n] = clock(); }
			else { std::cerr << "No more timers, " << label
				<< " will not be timed." << std::endl; }
		}
		void stop() { times[2*n+1] = clock(); n++;}
		void reset() { n=0; }
		void print();
	private:
		std::string labels[20];
		float times[40];
		int n;
};

void Timer::print()
{
	std::cout << std::endl;
	std::cout << "Action	::	time/s Time resolution = " << 1.f/(float)CLOCKS_PER_SEC << std::endl;
	std::cout << "------" << std::endl;
	for (int i=0; i < n; ++i)
		std::cout << labels[i] << " :: " << (times[2*i+1] - times[2*i+0])/(float)CLOCKS_PER_SEC << std::endl;
}

typedef std::vector<std::vector<float>> Array2D;

void initialize (Array2D& x, int n){
	int n2 = n+2;
	for (int i = 0; i < n2; i++){
		for (int j = 0; j < n2; j++){
			x[i][j] = ( (float)rand()/ (RAND_MAX) );
		}
	}
}

void smooth (Array2D& y, const Array2D x, int n, float a, float b, 
	float c){
	int i, j;
#pragma omp for private(j) schedule(static)
	for (i=1; i<=n; i++){
		//std::cout << i << std::endl;
//#pragma omp for 
		for (j=1; j<=n; j++){
			y[i][j] = a * (x[i-1][j-1] + x[i-1][j+1] + x[i+1][j-1]+ x[i+1][j+1]) 					+ b * (x[i-1][j] + x[i+1][j] + x[i][j-1] + x[i][j+1]) 
					+ c * x[i][j];
		}
	}
	//FUNC_END_TIMER;
}

void count(const Array2D x, const int n, const float t, int &res){
	//the boundary is not considered
	int j;
#pragma omp for private(j)
	for (int i=1; i <= n; i++){
//#pragma omp for
		for (j=1; j <= n; j++){
			if (x[i][j] < t){
				res ++;
			}
		}
	}
}

int main(){
	int num_thread;
	#pragma omp parallel
	{
		std::cout << omp_get_num_procs() << std::endl;
	}

	int num_of_threads;
#pragma omp parallel 
	#pragma omp single
	{
	num_of_threads = omp_get_num_threads();
	}
	
	/* timer of class Timer */
	Timer timer, timer2;

	//size of matrix (nxn)
	int n = 1 << 14;
	int nbx=0, nby=0;

	//convolution constants
	float a, b, c, t;
	a = 0.05;
	b = 0.1;
	c = 0.4;

	//threshold t
	t = 0.1;

	//allocate x
	Array2D x(n+2, std::vector<float>(n+2));

	//allocate y
	Array2D y(n+2, std::vector<float>(n+2));

	//initialize x
	initialize(x, n);	
	
	//smooth matrix x
	//timer.start("CPU: smooth");
	double t1 = omp_get_wtime();
#pragma omp parallel
	{
	smooth(y, x, n, a, b, c);
	}
	double t2 = omp_get_wtime();
	//timer.stop();

	double t_cnt = omp_get_wtime();	
#pragma omp parallel reduction(+:nbx)
	  {
	  count(x, n, t, nbx);
	  }
	double t_cnt_x = omp_get_wtime();
#pragma omp parallel reduction(+:nby)
	  {
	  count(y, n, t, nby);
	  }
	double t_cnt_y = omp_get_wtime();


	//count elements in first array
	//count(x, n, t, nbx);

	//count elements in second array
	//count(y, n, t, nby);


	//Formatted Output
	std::cout << std::endl;
	std::cout << "Summary" << std::endl;
	std::cout << "-------" << std::endl;
	std::cout << "Number of threads		::"	<< num_of_threads << std::endl;
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


	std::cout << "smooth time	::" << t2 - t1 << std::endl;
	std::cout << "count-x time	::" << t_cnt_x - t_cnt << std::endl;
	std::cout << "count-y time	::" << t_cnt_y - t_cnt_x << std::endl;

	return 0;
}
