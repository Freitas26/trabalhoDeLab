#include <stdio.h>
#include <mpi.h>

void main(int argc, char** argv) {
	MPI_Status status;
	int my_rank;
	double sum = 0.0;
	double a[256], b[256];
	int n=256, i=0;
	double total;
	int p; // número de processos
	int local_n; // intervalo local
	int local_a, local_b; // intervalo local0
	double aux = 0.0;
	double calcula(int inicio, int qtd, double* vet1, double* vet2);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// popula os vetores
	for(i; i<n; i++) {
		a[i] = i*0.5;
		b[i] = i*2.0;
	}

	// calcula "fatia" com base no rank
	int resto = n%p;

	if(my_rank < resto) {
		local_n = (n / p) + 1;
		local_a = (my_rank * local_n);
		printf("local_a: %d\n", local_a);
	}
	else {
		local_n = n / p;
		local_a = (my_rank * local_n) +resto;
		printf("local_a: %d\n", local_a);
	}
	local_b = local_a + local_n;

	// faz cálculos de verdade
	aux = calcula(local_a, local_n, a, b);

	MPI_Reduce(&aux, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(my_rank == 0){
		printf("Resultado: %f\n", total);
	}
	MPI_Finalize();
}


double calcula(int inicio, int qtd, double* vet1, double* vet2) {
	double aux = 0.0;
	for(int i = 0; i<qtd; i++) {
		aux = aux + vet1[inicio + i] * vet2[inicio + i];
	}
	return aux;
}