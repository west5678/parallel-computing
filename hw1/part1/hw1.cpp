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
	int n2 = n+2;
#pragma omp for private(j)
	for (int i=1; i<=n; i++){
//#pragma omp for 
		for (j=1; j<=n; j++){
			y[i*n2 + j] = a * (x[(i-1)*n2+(j-1)] + 
								x[(i-1)*n2+(j+1)] + 
								x[(i+1)*n2+(j-1)] + 
								x[(i+1)*n2+(j+1)])
						+ b * (x[(i-1)*n2+j] + 
								x[(i+1)*n2+j] + 
								x[i*n2+(j-1)] + 
								x[i*n2+(j+1)]) 
						+ c * x[i*n2+j];
		}
	}
	//FUNC_END_TIMER;
}

void count(float* x, const int n, const float t, int &res){
	//the boundary is not considered
	int j;
	int n2 = n+2;
#pragma omp for private(j)
	for (int i=1; i <= n; i++){
//#pragma omp for
		for (j=1; j <= n; j++){
			if (x[i*n2+j] < t){
				res ++;
			}
		}
	}
}

int main(){

	#pragma omp parallel
	{
		std::cout << omp_get_thread_num() << std::endl;
	}

	/* timer of class Timer */
	Timer timer, timer2;

	//size of matrix (nxn)
	int n = 1 << 14;
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
	
	//smooth matrix x
	timer.start("CPU: smooth");
#pragma omp parallel
	{
	smooth(y, x, n, a, b, c);
	}
	timer.stop();

	
	timer2.start("CPU: Count-XY");
	  timer.start("CPU: Count-X");
#pragma omp parallel reduction(+:nbx)
	  {
	  count(x, n, t, nbx);
	  }
	  timer.stop();
	  timer.start("CPU: Count-Y");
#pragma omp parallel reduction(+:nby)
	  {
	  count(y, n, t, nby);
	  }
	  timer.stop();
	timer2.stop();

	timer.print();
	timer2.print();

	//count elements in first array
	//count(x, n, t, nbx);

	//count elements in second array
	//count(y, n, t, nby);


	//Formatted Output
	std::cout << std::endl;
	std::cout << "Summary" << std::endl;
	std::cout << "-------" << std::endl;
	std::cout << "Number of threads		::"	<< omp_get_num_threads() << std::endl;
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




	return 0;
}
