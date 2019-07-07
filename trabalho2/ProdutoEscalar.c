#include <stdio.h>
#include <stdlib.h>

void main(){
	double sum = 0;
	double a[256], b[256], mult[256];
	int n = 256, i;

		for(i=0; i<n; i++){
			a[i]=i*0.5;
			b[i]=i*2.0;
		}
		for(i=1; i<n; i++){
			sum += a[i]*b[i];
		}

	printf("sum = %.2f\n", sum);
}