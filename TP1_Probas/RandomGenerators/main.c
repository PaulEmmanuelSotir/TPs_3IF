#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "file_attente.h"
#include "random_generation.h"
#include "lois_distributions.h"

#ifdef _WIN32
#include <intrin.h>
uint64_t rdtsc() {
	return __rdtsc();
}
#else
int/*uint64_t ??*/ rdtsc()
{
	// cette fonction cree un warning : c'est normal.
	__asm__ __volatile__("rdtsc");
}
#endif

//----------------------------------------------------------------------------- FORWARD DECLARATIONS

double Frequency(generator_array* random_values);
double p_value_monobit(generator_array* random_values);
double Runs(generator_array* data);

//--------------------------------------------------------------------------------------------- MAIN

int main()
{
	srand(rdtsc());

	// Ouverture du fichier de resultat des tests
	FILE* fichier = fopen("../_test_results.csv", "w");
	if (fichier == NULL)
		return -1;

	// Calcul et affichage de la P-valeur des différentes méthodes de génération de valeures aléatoires (csv)
	fprintf(fichier, "monobit pvalue, frequency, runs pvalue\n");
	for (size_t i = 0; i < 25; ++i)
	{
		// Génération des tableaux de valeurs aléatoires
		generator_array von_values = GenerateRandomValues(RANDOM_VALUE_COUNT, 13, "../_von_neumann.csv", generate_neumann); // de 0 à 9999 ? sur 14 ou 13 bits ?
		generator_array aes_values = GenerateRandomValues(RANDOM_VALUE_COUNT, 32, "../_aes.csv", generate_aes);
		generator_array twi_values = GenerateRandomValues(RANDOM_VALUE_COUNT, 32, "../_twister.csv", generate_twister);
		generator_array high_values = GenerateRandomValues(RANDOM_VALUE_COUNT, 4, "../_rand_high.csv", generate_rand_high);
		generator_array low_values = GenerateRandomValues(RANDOM_VALUE_COUNT, 4, "../_rand_low.csv", generate_rand_low);
		generator_array rand_values = GenerateRandomValues(RANDOM_VALUE_COUNT, 16 - 1, "../_rand.csv", rand);

		// Calcul et stockage des résultats des différents tests
		fprintf(fichier, "rand(), %f, %f, %f \n", p_value_monobit(&rand_values), Frequency(&rand_values), Runs(&rand_values));
		fprintf(fichier, "Von Neumann, %f, %f, %f\n", p_value_monobit(&von_values), Frequency(&von_values), Runs(&von_values));
		fprintf(fichier, "Mersenne-Twister, %f, %f, %f\n", p_value_monobit(&twi_values), Frequency(&twi_values), Runs(&twi_values));
		fprintf(fichier, "AES, %f, %f, %f\n", p_value_monobit(&aes_values), Frequency(&aes_values), Runs(&aes_values));

		// Libération de la mémoire
		destroy(&von_values); destroy(&aes_values); destroy(&twi_values); destroy(&high_values); destroy(&low_values); destroy(&rand_values);
	}

	fclose(fichier);

	// Test de la fonction f_inversion (distribution de f avec la méthode d'inversion)
	struct timeval tps1, tps2;
	volatile double test;
	gettimeofday(&tps1, NULL);
	for (size_t i = 0; i < 3000; ++i)
		test = f_inversion();
	gettimeofday(&tps2, NULL);
	printf("Temps d'execution du calcul de 3000 valeurs de la distribution f (inversion): %ld us\n", tps2.tv_usec - tps1.tv_usec);

	// Test de la fonction f_inversion (distribution de f avec la méthode par rejet)
	gettimeofday(&tps1, NULL);
	for (size_t i = 0; i < 3000; ++i)
		test = f_rejet();
	gettimeofday(&tps2, NULL);
	printf("Temps d'execution du calcul de 3000 valeurs de la distribution f (rejet): %ld us\n", tps2.tv_usec - tps1.tv_usec);


	return 0;
}


//------------------------------------------------------------------------ TEST DE FREQUENCE MONOBIT

double Frequency(generator_array* random_values)
{
	int sum = 0;
	for (size_t i = 0; i < size(random_values); ++i)
		sum += 2 * get_bit(random_values, i) - 1;

	return abs(sum) / sqrt(size(random_values));
}

// Finds the p_value of 'value_count' integers encoded using 'bit_count' bits
double p_value_monobit(generator_array* random_values)
{
	return erfc(Frequency(random_values) / sqrt(2));
}


//------------------------------------------------------------------------------------ TEST DES RUNS

double Runs(generator_array* data)
{
	size_t n = size(data);

	// Compte le nombre de '1'
	unsigned int one_count = 0;
	for (size_t i = 0; i < size(data); ++i)
		one_count += get_bit(data, i);
	double p = one_count / (double)n;

	// Vérifie si l'on peut arr^ter le test ici
	if (fabs(p - 1 / 2.0) >= 2.0 / sqrt(n))
		return 0.0;

	// Calcule Vn(obs)
	unsigned int Vobs = 1;
	for (size_t i = 0; i < size(data) - 1; ++i)
		Vobs += ((get_bit(data, i) == get_bit(data, i + 1)) ? 0 : 1);

	// Retourne la p-valeur du test
	return erfc(fabs(Vobs - 2.0 * one_count*(1 - p)) / (2.0 * sqrt(2.0 * n)*p*(1.0 - p)));
}
