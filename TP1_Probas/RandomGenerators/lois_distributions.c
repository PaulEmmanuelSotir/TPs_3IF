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

// Loi uniforme
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
	static double c = 2.0 / 0.48045301391820139; // 2/log(2)^2

	double U, Y; // Deux variables issues de deux lois de probabilitées uniformes indépendantes
	double f;
	do
	{
		U = 1 / 2.0 + generate_aes() / n;
		Y = 1 / 2.0 + generate_twister() / n;

		f = c * log(1 + Y) / (1 + Y); // Calcul de f(Y), avec Y toujours compris entre 0 et 1
	} while (U <= f / (c * Y)); // On tire de nouvelles valeures tant que la condition n'est pas vérifiée (rejet)

	return Y; // Y suit alors la loi de probabilitées decrite par f
}
