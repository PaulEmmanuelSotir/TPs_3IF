#include <stdlib.h>
#include "N.h"

int main()
{
	double v[N];
	double sum = 0;

	for(size_t i = 0; i < N; i++)
		sum += v[i];
	
	return EXIT_SUCCESS;
}
