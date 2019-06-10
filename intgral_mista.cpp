#include <stdio.h>
#include <mpi.h>

// mpic++ -fopenmp intgral_mista.cpp -o intgral_mista
// mpiexec -np 2 ./intgral_mista

int main(int argc, char** argv) {
	int my_rank;
	int p; // número de processos
	float a=0.0, b=1.0; // intervalo a calcular
	int n=1024; // número de trapezóides
	float h; // base do trapezóide
	float local_a, local_b; // intervalo local
	int local_n; // número de trapezóides local
	float integral; // integral no meu intervalo
	float total; // integral total
	int source; // remetente da integral
	int dest=0; // destino das integrais (nó 0)
	int tag=200; // tipo de mensagem (único)
	MPI_Status status;

	float calcula(float local_a, float local_b, int local_n);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	int resto = n%p;
	h = (b-a) / n;

	if(my_rank < resto) {
		local_n = (n / p) + 1;
		local_a = a + (my_rank * local_n * h);
	}
	else {
		local_n = n / p;
		local_a = a + (my_rank * local_n * h) + ((my_rank) * 1 * h);
	}
	local_b = local_a + local_n * h;

	integral = calcula(local_a, local_b, local_n);

	MPI_Reduce(&integral, &total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(my_rank == 0){
		printf("Resultado: %f\n", total);
	}
	MPI_Finalize();
  return 0;
}

float calcula(float local_a, float local_b, int local_n) {
  int i;
  float resultado = 0;
  // float altura;
  float largura = (local_b - local_a)/(local_n);
  // printf("local_a: %f\n", local_a);
  // printf("local_b: %f\n", local_b);
  // printf("local_n: %d\n", local_n);

  #pragma omp parallel for num_threads(2) private(i) reduction(+:resultado)
  for(i=1; i<(int)local_n; i++){
    float x_atual = local_a + ((i-1) * largura); // valor inicial + passos que dei
    float altura = x_atual*x_atual; // calcula f(x) naquele ponto
    // printf("x_atual: %f\n", x_atual);
    resultado+= (altura*largura);
  }
}
