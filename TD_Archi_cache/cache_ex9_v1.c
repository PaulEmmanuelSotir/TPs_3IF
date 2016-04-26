#include <stdlib.h>
#include "N.h"

double A[N][N], B[N][N], C[N][N];

int main()
{
	for(size_t i = 0; i<N; i++) {
		for(size_t j = 0; j < N; j++) {
			double r = 0;
			for(size_t k = 0; k < N; k++)
				r += A[i][k]*B[k][j];
			C[i][j] += r;
		}
	}
	
	return EXIT_SUCCESS;
}
