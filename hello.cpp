#include <omp.h>
#include <stdio.h>

int main(){
	printf("hello, from master\n");
	
	#pragma omp parallel
	{
		printf("id%d\n", omp_get_thread_num());
	}
}
