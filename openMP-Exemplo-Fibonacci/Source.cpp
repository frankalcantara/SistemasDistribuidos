/* OpenMP code to compute Fibonacci */
#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

static int fib(int);

int main(){
	int nthreads, tid;
	int n = 25;
#pragma omp parallel num_threads(4) private(tid)
	{
#pragma omp 
		{
			tid = omp_get_thread_num();
			printf("Fib(%d) = %d no thread %d\n", n, fib(n), tid);
		}
	}
	system("Pause");
}

static int fib(int n){
		int i, j, id;
		if ( n < 2) return n;
#pragma omp task shared(i) private(id)
		{
			i = fib(n - 1);
		}
#pragma omp task shared(j) private(id)
		{
			j = fib(n	-	2);
		}
		return (i + j);
}