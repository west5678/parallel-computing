#include <iostream>
#include <vector>
#include <stdlib.h>

#include<grvy.h>	//grvy for performance timing
#include<sys/time.h>
#include<time.h>
#include<unistd.h>

// Convenience timer macros for begin/end functions
//
#define FUNC_BEGIN_TIMER gt.BeginTimer(__func__);
#define FUNC_END_TIMER   gt.EndTimer  (__func__);

GRVY::GRVY_Timer_Class gt;              // GRVY Timer

std::vector<std::vector<double>> randMatrix (int m, int n){
	std::vector<std::vector<double>> x (m, std::vector<double> (n, 0.0));
	FUNC_BEGIN_TIMER;
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			x[i][j] = ((double) rand() / (RAND_MAX));
		}
	}
	FUNC_END_TIMER;
	return x;
}

std::vector<std::vector<double>> smooth (int m, int n, double a, double b, 
	double c, std::vector<std::vector<double>> x){
	FUNC_BEGIN_TIMER;
	std::vector<std::vector<double>> y (m, std::vector<double> (n, 1.0));
	for (int i=1; i<m-1; i++){
		for (int j=1; j<n-1; j++){
			y[i][j] = a * (x[i-1][j-1] + x[i-1][j+1] + x[i+1][j-1]
			+ x[i+1][j+1]) + b * (x[i-1][j] + x[i+1][j] 
			+ x[i][j-1] + x[i][j+1]) + c * x[i][j];
		}
	}
	std::cout.precision(15);
	FUNC_END_TIMER;
	return y;
}

int count(std::vector<std::vector<double>> x, double t){
	int res = 0;
	FUNC_BEGIN_TIMER;
	for (auto row: x){
		for (auto c : row){
			if (c < t){
				res ++;
			}
		}
	}
	FUNC_END_TIMER;
	return res;
}

int main(){
	gt.Init("hw0 Timing");
	gt.BeginTimer("Main Program");

	//generate first m*n array(x) with random numbers
	int m, n;
	double a, b, c, t;
	m = 10;
	n = 10;
	a = 0.0;
	b = 0.125;
	c = 0.5;
	t = 0.5;
	//generate random matrix
	std::vector<std::vector<double>> x = randMatrix(m, n);
	
	//smooth matrix x
	std::vector<std::vector<double>> y = smooth(m, n, a, b, c, x);

	//Counting of elements below threshold 
	std::cout << "# of elements in x below threshold: " << count(x, t) << std::endl;
	std::cout << "# of elements in y below threshold: " << count(y, t) << std::endl;

	gt.EndTimer("Main Program");
	gt.Finalize();
	gt.Summarize();
	gt.Reset();

	return 0;
}
