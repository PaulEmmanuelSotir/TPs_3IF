#include <stdlib.h>

#include "N.h"

double A[N][N], B[N][N], C[N][N];

int main()
{
	for(size_t i = 0; i<N; i++) {
		for(size_t k = 0; k < N; k++) {
			double r = A[i][k];
			for(size_t j = 0; j < N; j++)
				C[i][j] += B[k][j]*r;
		}
	}
	
	return EXIT_SUCCESS;
}
