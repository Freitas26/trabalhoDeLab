#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(){
    float local_n = 1024;
    float integral = 0;
    int i;
    float altura;
    float largura = (1/local_n);

    #pragma omp parallel for private(i) reduction(+:integral)
    for(i = 1; i<(int)local_n; i++){
        altura = (i/local_n)*(i/local_n); // calcula f(x) naquele ponto
        integral+= (altura*largura);
    }

    printf("%f\n", integral);
    return 0;
}
