/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <string.h>
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	
	double *res = calloc(N * N, sizeof(double));
	double *res2 = calloc(N * N, sizeof(double));
	double *res3 = calloc(N * N, sizeof(double));
	

	// Calculăm A * B *At
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				/// Ținem cont că A e matrice superior triunghiulară
				if (i <= k) {
					res[i * N + j] += A[i * N + k] * B[k * N + j];
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				// Ținem cont că At e matrice inferior triunghiulară
				if (k >= j) {
					res2[i * N + j] += res[i * N + k] * A[j * N + k];
				}
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%lf ", res2[i * N + j]);
		}
		printf("\n");
	}
	printf("\n");
	
	
	// Calculăm Bt * Bt si adunam ce am calculat mai sus
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				res3[i * N + j] += B[k * N + i] * B[j * N + k];
			}
			res3[i * N + j] += res2[i * N + j];
		}
	}


	free(res);
	free(res2);
	
	return res3;
}
