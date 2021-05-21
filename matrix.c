//
// ParallelMatrix.c
// Practica4
//
// Created by Beatriz Paulina Garcia Salgado
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////No cambiar este segmento////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "matrix.h"

int getNumberOfCPUs()
/*Gets the number of available cores at the momment
Input: void
Output: number of available cores*/
{
	int numThreads;
	numThreads = omp_get_max_threads();
	return numThreads;
}

int checkSumAll(long double* counter, long double* M, int sizeMat)
/*Performs the addition of all the elements of a square matrix to check operations
Input:	pointer to save the result
	pointer to the matrix
	size of the square matrix
Output: EXIT_FAILURE; EXIT_SUCCESS*/
{
	int element, totalElem;
	if(!counter || !M)
	{
		printf("Error in input pointers\n");
		return EXIT_FAILURE;
	}
	
	totalElem = sizeMat * sizeMat;
	*counter = 0;
	for(element = 0; element < totalElem; element++)
	{
		*counter = *counter + *(M + element);
	}
	
	return EXIT_SUCCESS;
}
	

int ompParallelMatrixSum(long double** result, long double* A, long double* B, int sizeMat)
/*Computes the addition of two square matrices: result = A + B
Input:	pointer to save the result
	pointer to matrix A
	pointer to matrix B
	size of the square matrices
Output: EXIT_FAILURE; EXIT_SUCCESS*/
{
	int element, totalElem;
	
	if(!*result || !A || !B)
	{
		printf("Error in a matrix pointer\n");
		return EXIT_FAILURE;
	}
	
	totalElem = sizeMat * sizeMat;
	
	#pragma omp parallel for
	for(element = 0; element < totalElem; element++)
	{
		*(*result + element) = *(A + element) + *(B + element);
	}
	
	return EXIT_SUCCESS;
}

int matrixSum(long double** result, long double* A, long double* B, int sizeMat)
/*Computes the addition of two square matrices: result = A + B
Input:	pointer to save the result
	pointer to matrix A
	pointer to matrix B
	size of the square matrices
Output: EXIT_FAILURE; EXIT_SUCCESS*/
{
	int element, totalElem;
	
	if(!*result || !A || !B)
	{
		printf("Error in a matrix pointer\n");
		return EXIT_FAILURE;
	}
	
	totalElem = sizeMat * sizeMat;
	
	for(element = 0; element < totalElem; element++)
	{
		*(*result + element) = *(A + element) + *(B + element);
	}
	
	return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Inserte el código solicitado en la práctica aqui.
int matrix_multi (
	long double *result, long double *A, long double *B, int mat_size
) {

	if(!result || !A || !B)
	{
		printf("Error in a matrix pointer\n");
		return EXIT_FAILURE;
	}

	int c = 0, d = 0, k = 0;
	// long double tot = 0;
	long double *res = result;
	for (c = 0; c < mat_size; c++) {
		for (d = 0; d < mat_size; d++) {
			for (k = 0; k < mat_size; k++) {
				// tot = tot + A[c][k] * B[k][d];
				*(res+c*mat_size+d) += *(A + c*mat_size + k) * *(B+k*mat_size+d);
			}

			// result[c][d] = tot;
			// tot = 0;
		}
	}

	return EXIT_SUCCESS;

}

int matrix_multi_parallel (
	long double *result, long double *A, long double *B, int mat_size
) {

	if(!result || !A || !B)
	{
		printf("Error in a matrix pointer\n");
		return EXIT_FAILURE;
	}

	long double *res = result;
	#pragma omp parallel
    {
        int i, j, k;
        #pragma omp for
        for (i = 0; i < mat_size; i++) { 
            for (j = 0; j < mat_size; j++) {
                double dot  = 0;
                for (k = 0; k < mat_size; k++) {
                    dot += A[i*mat_size+k]*B[k*mat_size+j];
                } 
                res[i*mat_size+j ] = dot;
            }
        }

    }

	return EXIT_SUCCESS;

}

long double matrix_max (long double* A, int sizeMat)
{
	int element, totalElem;
	
	long double max = 0;
	totalElem = sizeMat * sizeMat;
	for(element = 0; element < totalElem; element++)
	{
		if (*(A + element) > max) {
			max = *(A + element);
		}
	}
	
	return max;
}
long double matrix_max_multi (long double* A, int sizeMat)
{
	
	long double max = 0;
	#pragma omp parallel
	{
		
		int element, totalElem;
		totalElem = sizeMat * sizeMat;
		#pragma omp parallel for shared(max)
		for(element = 0; element < totalElem; element++)
		{
			if (*(A + element) > max) {
				max = *(A + element);
			}
		}
	}
	
	return max;
}
