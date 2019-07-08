#include <stdio.h>
#include <stdlib.h>

void main(){
	long double sum=0,mult = 1;
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
	#pragma omp parallel shared(a, b) private(i) num_threads(2) reduction(+:sum) reduction(*:mult)
	{
		#pragma omp sections nowait
		{
			#pragma omp section
			for(i=0; i<n; i++){
				sum+=a[i]*b[i];
			}
			#pragma omp section 
			for(i=1; i<n; i++){
				mult*=a[i]*b[i];
			}
		}//end of sections
	}

	printf("sum = %.2Lf\n", sum);
	printf("mult = %.2Lf\n", mult);
}
