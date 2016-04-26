#include <stdlib.h>
#include "N.h"

int main()
{
	double v[N][N];
	double sum = 0;

	for(size_t i = 0; i < N; i++) {
		for(size_t j = 0; j < N; j++)
			sum += v[i][j];
	}
	
	return EXIT_SUCCESS;
}
