#include <iostream>
#include <omp.h>

using namespace std;

int main(){
#pragma omp parallel
	{
		cout << "parallel" << endl;
	}
	cout << "this is the end of the program" << endl;
	return 0;
}
