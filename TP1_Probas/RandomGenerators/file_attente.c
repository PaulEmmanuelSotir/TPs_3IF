#include "file_attente.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "lois_distributions.h"

void init(file_attente* fa)
{
	memset(fa->arrivee, 0.0, ARRAY_MAX_SIZE);
	memset(fa->depart, 0.0, ARRAY_MAX_SIZE);
}

file_attente FileMM1(double lambda, double mu, double D)
{
	file_attente fa;
	init(&fa);

	// TODO:...

	return fa;
}