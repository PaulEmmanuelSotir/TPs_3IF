#include "lois_distributions.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "random_generation.h"

//----------------------------------------------------------------------------- LOIS DE DISTRIBUTION

double Alea()
{
	static double n = 4294967296; // 2^32
	return 1 / 2.0 + generate_aes() / n;
}

double Exponentielle(double lambda)
{
	return -log(1 - Alea()) / lambda;
}

double Gauss(double sigma, double m)
{
	static double n = 4294967296; // 2^32
	static double Pi = 3.14159265359;
	double U = 1 / 2.0 + generate_aes() / n;
	double V = 1 / 2.0 + generate_twister() / n;
	return m + sigma * sqrt(-log(U)) * cos(2 * Pi * V);
}

double f_inversion()
{
	return exp(sqrt(Alea()) * log(2)) - 1;
}

double f_rejet()
{
	static double n = 4294967296; // 2^32
	static double c = 2.0 / (log(2)*log(2));

	double U, Y;
	do
	{
		U = 1 / 2.0 + generate_aes() / n;
		Y = 1 / 2.0 + generate_twister() / n;

	} while (0/*U > f(Y) / (c * g(Y))*/); // TODO: complèter
	return 0;//Y;
}