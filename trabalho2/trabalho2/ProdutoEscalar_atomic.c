#include <stdio.h>
#include <stdlib.h>

void main(){
	double sum = 0, aux;
	double a[256], b[256];
	int n = 256, i;

	for(i=0; i<n; i++){
		a[i]=i*0.5;
		b[i]=i*2.0;
	}

	#pragma omp parallel shared(a, b, n, sum) private(i, aux) num_threads(2)
	{
		aux=0;

		#pragma omp for
		for(i=0; i<n; i++){
			aux+=a[i]*b[i];
		}

		#pragma omp atomic
		sum = sum + aux;
	}

	printf("sum = %.2f\n", sum);
}
