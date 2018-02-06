#include <iostream>
#include <vector>
#include <stdlib.h>

//#include<grvy.h>	//grvy for performance timing
#include<sys/time.h>
#include<time.h>
#include<unistd.h>

// Convenience timer macros for begin/end functions
//
//#define FUNC_BEGIN_TIMER gt.BeginTimer(__func__);
//#define FUNC_END_TIMER   gt.EndTimer  (__func__);

//GRVY::GRVY_Timer_Class gt;              // GRVY Timer

typedef std::vector<std::vector<float>> Array2D;

void initialize (Array2D& x, int n){
	//FUNC_BEGIN_TIMER;
	for (int i = 0; i < n; i++){
		std::vector<float> row;
		for (int j = 0; j < n; j++){
			row.push_back( (float)rand() / (RAND_MAX) );
		}
		x.push_back(row);
	}
	//FUNC_END_TIMER;
}

void smooth (const Array2D x, Array2D& y, int n, float a, float b, 
	float c){
	//FUNC_BEGIN_TIMER;
	for (int i = 0; i < n; i++){
		y.push_back(std::vector<float> (n, 0.0));
	} 
	for (int i=1; i<n-1; i++){
		for (int j=1; j<n-1; j++){
			y[i][j] = a * (x[i-1][j-1] + x[i-1][j+1] + x[i+1][j-1]
			+ x[i+1][j+1]) + b * (x[i-1][j] + x[i+1][j] 
			+ x[i][j-1] + x[i][j+1]) + c * x[i][j];
		}
	}
	//FUNC_END_TIMER;
}

int count(const std::vector<std::vector<float>> x, float t){
	int res = 0;
	//FUNC_BEGIN_TIMER;
	for (auto row: x){
		for (auto c : row){
			if (c < t){
				res ++;
			}
		}
	}
	//FUNC_END_TIMER;
	return res;
}

int main(){
	//gt.Init("hw0 Timing");
	//gt.BeginTimer("Main Program");

	//size of matrix (nxn)
	int n = 16384+2;

	//convolution constants
	float a, b, c, t;
	a = 0.05;
	b = 0.1;
	c = 0.4;

	//threshold t
	t = 0.1;

	//generate random matrix
	Array2D x;
	initialize(x, n);	
	
	//smooth matrix x
	Array2D y;
	smooth(x, y, n, a, b, c);

	//Counting of elements below threshold 
	std::cout << "total number of elements in a column/row of an array: " <<n << std::endl;
	std::cout << "total number of inner elements in a column/row of an array: " << n - 2 << std::endl;
	std::cout << "total number of elements in an array: " << n*n << std::endl;
	std::cout << "total number of inner elements in an array: " << (n-2)*(n-2)<<std::endl;
	std::cout << "Size of array: " << sizeof(x) << std::endl;
	std::cout << "# of elements in x below threshold: " << count(x, t) << std::endl;
	std::cout << "# of elements in y below threshold: " << count(y, t) << std::endl;
	std::cout << x.size()*x[0].size()*sizeof(x[0][0]) << std::endl;

/*
	gt.EndTimer("Main Program");
	gt.Finalize();
	gt.Summarize();
	gt.Reset();
*/
	return 0;
}
