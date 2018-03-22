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
			x[i][j] = ( random()/ (RAND_MAX) );
		}
	}
}

void smooth (Array2D& y, const Array2D x, int n, float a, float b, 
	float c){
	int j;
	for (int i=1; i<=n; i++){
		for (j=1; j<=n; j++){
			y[i][j] = a * (x[i-1][j-1] + x[i-1][j+1] + x[i+1][j-1]+ x[i+1][j+1]) 					+ b * (x[i-1][j] + x[i+1][j] + x[i][j-1] + x[i][j+1]) 
					+ c * x[i][j];
		}
	}
}

void count(const Array2D x, const int n, const float t, int &res){
	//the boundary is not considered
	int j;
	for (int i=1; i <= n; i++){
		for (j=1; j <= n; j++){
			if (x[i][j] < t){
				res ++;
			}
		}
	}
}

int main(){


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
	timer.start("CPU: smooth");
	smooth(y, x, n, a, b, c);
	timer.stop();

	
	timer2.start("CPU: Count-XY");
	  timer.start("CPU: Count-X");
	  count(x, n, t, nbx);
	  timer.stop();
	  timer.start("CPU: Count-Y");
	  count(y, n, t, nby);
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
	std::cout << "Number of elements in a row/column		::" << n+2 << std::endl;
	std::cout << "Number of inner elements in a row/column	::" << n << std::endl;
	std::cout << "Total number of elements					::" << (n+2)*(n+2) << std::endl;
	std::cout << "Total number of inner elements			::" << n*n << std::endl;
	std::cout << "Memory (GB) used per array				::" << (n+2)*(n+2)*sizeof(float)/float(1024) << std::endl;
	std::cout << "Threshold									::" << t << std::endl;
	std::cout << "Smoothing constants (a, b, c)				::" << a << " " << b << " " << c << std::endl;


	std::cout << "Number of elements below threshold (X)	::" << nbx << std::endl;
	std::cout << "Fraction of elements below threshold		::" << nbx / (float)(n*n) << std::endl;
	std::cout << "Number of elements below threshold (Y)	::" << nby << std::endl;
	std::cout << "Fraction of elements below threshold		::" << nby / (float)(n*n) << std::endl;


/*
	//Counting of elements below threshold 
	std::cout << "total number of elements in a column/row of an array: " <<n << std::endl;
	std::cout << "total number of inner elements in a column/row of an array: " << n - 2 << std::endl;
	std::cout << "total number of elements in an array: " << n*n << std::endl;
	std::cout << "total number of inner elements in an array: " << (n-2)*(n-2)<<std::endl;
	std::cout << "Size of array: " << sizeof(x) << std::endl;
	std::cout << "# of elements in x below threshold: " << count(x, t) << std::endl;
	std::cout << "# of elements in y below threshold: " << count(y, t) << std::endl;
	std::cout << x.size()*x[0].size()*sizeof(x[0][0]) << std::endl;
*/

	/*
	gt.EndTimer("Main Program");
	gt.Finalize();
	gt.Summarize();
	gt.Reset();
*/

	return 0;
}
