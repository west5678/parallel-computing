#include <iostream>
#include <omp.h>
#include <time.h>  

using namespace std;

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
		std::cout << "Action    ::  time/s Time resolution = " << 1.f/(float)CLOCKS_PER_SEC << std::endl;
		std::cout << "------" << std::endl;
		for (int i=0; i < n; ++i)
			std::cout << labels[i] << " :: " << (times[2*i+1] - times[2*i+0])/(float)CLOCKS_PER_SEC << std::endl;
}


int main(){
#pragma omp parallel
	{
		cout << omp_get_thread_num() << endl;
	}

	Timer timer;
	int res = 0, N = 1 << 4;
	int i, j;
	timer.start("test loop");
#pragma omp parallel for reduction (+:res) private(j)
	for (i=0; i<N; i++){
		cout << i <<endl;
		for (j=0; j<N; j++){
			res += i*j;
			res -= (i+j);
			res -= i*j;
			res += (i+j);
			res += i;
		}
	}
	timer.stop();

	cout << res << endl;
	timer.print();
	return 0;
}
