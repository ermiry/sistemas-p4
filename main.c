#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "matrix.h"

double timer_get_current_time (void) {

	struct timeval time = { 0 };
	return !gettimeofday (&time, NULL) ?
		(double) time.tv_sec + (double) time.tv_usec * .000001 : 0;

}

int main(int argc, char** argv)
{
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////No cambiar este segmento////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Variables for matrix operations
	long double* A = NULL;
	long double* B = NULL;
	long double* C = NULL;
	long double count;
	int sizeMat = 100;
	int row,col;
	
	//Variables for thread management and time
	int numThreads;
	struct timespec t0, t1;
	double tiempoMedido;
	
	//Allocate matrices
	A = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	B = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	C = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	if(!A || !B || !C)
	{
		printf("Cannot allocate the matrices\n");
		exit(EXIT_FAILURE);
	}
	
	//Set the maximum number of cores as available threads
	numThreads = getNumberOfCPUs();
	printf("Available cores: %d\n",numThreads);
	omp_set_num_threads(numThreads);
	
	//Initialise the matrices
	for(row = 0; row < sizeMat; row++)
	{
		count = 1;
		for(col = 0; col < sizeMat; col++)
		{
			*(A + row * sizeMat + col) = count;
			*(B + row * sizeMat + col) = 2;
			count++;
		}
	}
	
	checkSumAll(&count, A, sizeMat);
	printf("The addition of all components of A is %Lf\n",count);
	
	checkSumAll(&count, B, sizeMat);
	printf("The addition of all components of B is %Lf\n",count);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//La multiplicacion a realizar es A*B.
	//El maximo debe obtenerse de la matriz A.
	
	//Inserte el codigo solicitado en la practica aqui.
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// multi singlethread
	double start = timer_get_current_time ();
	matrix_multi (C, A, B, sizeMat);
	double matrix_multi_single_time = timer_get_current_time () - start;

	checkSumAll(&count, C, sizeMat);
	printf("The addition of all components of A X B in one thread is %Lf\n",count);
	printf ("process time: %f secs\n", matrix_multi_single_time);

	// reset result
	memset(C, 0, sizeMat * sizeMat * sizeof(long double));

	// multi multithread
	start = timer_get_current_time ();
	matrix_multi_parallel (C, A, B, sizeMat);
	double matrix_multi_multi_time = timer_get_current_time () - start;
	checkSumAll(&count, C, sizeMat);
	printf("The addition of all components of A X B in multiple threads is %Lf\n",count);
	printf ("process time: %f secs\n", matrix_multi_multi_time);

	// max singlethread
	start = timer_get_current_time ();
	long double max = matrix_max (A, sizeMat);
	double matrix_max_single_time = timer_get_current_time () - start;
	printf("The max in A in one thread is %Lf\n",max);
	printf ("process time: %f secs\n", matrix_max_single_time);

	long double max_multi = matrix_max_multi (A, sizeMat);
	double matrix_max_multi_time = timer_get_current_time () - start;
	printf("The max in A in multiple threads is %Lf\n",max_multi);
	printf ("process time: %f secs\n", matrix_max_multi_time);

	printf ("\n\nTimes\n\n");
	printf ("------------------------------------------------\n");
	printf ("| Process    |  Single         |    Multi      |\n");
	printf ("------------------------------------------------\n");
	printf ("| Multi      | %6f secs   | %6f secs |\n", matrix_multi_single_time, matrix_multi_multi_time);
	printf ("| Max        | %6f secs   | %6f secs |\n", matrix_max_single_time, matrix_max_multi_time);
	printf ("------------------------------------------------\n");
	printf ("\n");

	return EXIT_SUCCESS;
}
