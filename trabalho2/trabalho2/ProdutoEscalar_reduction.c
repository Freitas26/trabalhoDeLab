#include <stdio.h>
#include <stdlib.h>

void main(){
	double sum = 0;
	double a[256], b[256];
	int n = 256, i;

	#pragma omp parallel shared(a, b, n) private(i) num_threads(2)
	{
		#pragma omp for
		for(i=0; i<n; i++){
			a[i]=i*0.5;
			b[i]=i*2.0;
		}
	}
	#pragma omp parallel shared(a, b) private(i) num_threads(2) reduction(+:sum)
	{
		#pragma omp for
		for(i=0; i<n; i++){
			sum+=a[i]*b[i];
		}
	}

	printf("sum = %.2f\n", sum);
}