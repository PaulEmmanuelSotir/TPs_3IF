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

int main(int argc, char *argv[])
{
	srand(rdtsc());

	// Ouverture du fichier de resultat des tests des générateurs d'aléatoire
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

	if (argc == 1) //----------------------------------- Test des fonctions simulant une loi de distribution f
	{
		double f_distrib_inv[3000], f_distrib_rej[3000];

		// Test de la fonction f_inversion (distribution de f avec la méthode d'inversion)
		struct timeval tps1, tps2;
		gettimeofday(&tps1, NULL);
		for (size_t i = 0; i < 3000; ++i)
			f_distrib_inv[i] = f_inversion();
		gettimeofday(&tps2, NULL);
		printf("Temps d'execution du calcul de 3000 valeurs de la distribution f (inversion): %ld us\n", tps2.tv_usec - tps1.tv_usec);

		// Test de la fonction f_inversion (distribution de f avec la méthode par rejet)
		struct timeval tps3, tps4;
		gettimeofday(&tps3, NULL);
		for (size_t i = 0; i < 3000; ++i)
			f_distrib_rej[i] = f_rejet();
		gettimeofday(&tps4, NULL);
		printf("Temps d'execution du calcul de 3000 valeurs de la distribution f (rejet): %ld us\n", tps4.tv_usec - tps3.tv_usec);
	
		// Ouverture du fichier où l'on vas enregister les distributions de f obtenues
		FILE* fichier_f = fopen("../_distributions_f.csv", "w");
		if (fichier_f == NULL)
			return -1;

		fprintf(fichier, "inversion, rejet\n");
		for (size_t i = 0; i < 3000; ++i)
			fprintf(fichier, "%lf, %lf\n", f_distrib_inv[i], f_distrib_rej[i]);

		fclose(fichier_f);
	}
	else if (argc == 2) //----------------------------------- File d'attente MM1
	{
		double lambda = 12.0 / 60;
		file_attente fa = FileMM1(lambda, 20.0 / 60, 3 * 60);
		fprint(&fa, "../_file_mm1.csv");

		// Calcul de l'évolution de la liste d'attante MM1
		evolution evol = get_evolution(&fa, 3 * 60);
		fprint_evol(&evol, "../_evolution.csv");

		// Affichage du nombre moyen de client dans le système et du temps moyen de présence
		double E_N = get_number_mean(&evol);
		double E_W = get_time_mean(&fa, &evol);
		printf("Nombre moyen de clients dans la file : E(N) = %lf clients\n", E_N);
		printf("Temps moyen de présence d'un client dans la file : E(W) = %lf min\n", E_W);
		printf("D'ou, lambda * E(W) = %lf\n", lambda * E_W);
	}
	else if (argc == 3) //-----------------------------------File d'attente MMN
	{
		// Création et enregistrement d'une file M/M/N avec n = 2
		double lambda = 12.0 / 60;
		file_attente mm2 = FileMMN(lambda, 20.0 / 60, 3 * 60, 2);
		fprint(&mm2, "../_file_mm2.csv");
	}

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
