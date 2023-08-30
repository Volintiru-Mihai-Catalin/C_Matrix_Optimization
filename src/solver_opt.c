/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <string.h>
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");

	double *res = calloc(N * N, sizeof(double));
	double *res2 = calloc(N * N, sizeof(double));
	// double *res3 = calloc(N * N, sizeof(double));
	
	
	// Calculăm înmulțirea A * B * At in stilul i-k-j

	for (int i = 0; i < N; i++) {
		double *orig_A = &A[i * N];
		double *orig_res = &res[i * N];
		double *orig_B = &B[0];
		for (int k = 0; k < N; k++) {
			double *pB = orig_B;
			double *p_res = orig_res;
			register double vA = *orig_A;
			// Ținem cont că At e matrice superior triunghiulară
			if (i <= k) {
				for (int j = 0; j < N; j++) {
					*p_res += vA * *pB;
					p_res++;
					pB++;
				}
			}
			orig_A++;
			orig_B += N; 
		}
	}
	
	for (int i = 0; i < N; i++) {
		register double *orig_res = &res[i * N];
		register double *orig_At = A;
		for (int j = 0; j < N; j++) {
			register double suma = 0.0;
			register double *p_res = orig_res;
			register double *pAt = orig_At + j * N; 
			for (int k = 0; k < N; k++) {
				// Ținem cont că At e matrice inferior triunghiulară
				if (k >= j) {
					suma += *p_res * *pAt;
				}
				p_res++;
				pAt++;
			}
			*(res2 + i * N + j) = suma;
		}
	}

	// Calculăm Bt * Bt si adunam ce am calculat mai sus
	for (int i = 0; i < N; i++) {
		register double *p_res = &res[i];
		register double *p_res2 = &res2[i];
		register double *orig_pBt_right = &B[i * N];
		for (int j = 0; j < N; j++) {
			register double suma = 0.0;
			register double *pBt_right = orig_pBt_right;
			register double *pBt_left = &B[j];
			for (int k = 0; k < N; k++) {
				suma += *pBt_left * *pBt_right;
				pBt_right++;
				pBt_left += N;
			}
			*p_res = suma + *p_res2;
			p_res += N;
			p_res2 += N;
		}
	}

	free(res2);

	return res;	
}
