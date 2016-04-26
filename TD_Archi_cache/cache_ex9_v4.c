#include <stdlib.h>
#include "N.h"

double A[N][N], B[N][N], C[N][N];

int main()
{
	for(size_t k = 0; k<N; k++) {
		for(size_t j = 0; j < N; j++) {
			double r = B[k][j];
			for(size_t i = 0; i < N; i++)
				C[i][j] += A[i][k]*r;
		}
	}
	
	return EXIT_SUCCESS;
}
