#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "von_neumann.h"
#include "aes.h"
#include "mersenne_twister.h"

#define ARRAY_MAX_SIZE 1000
#define RANDOM_VALUE_COUNT 1024

int rdtsc()
{
	// cette fonction cree un warning : c'est normal.
	__asm__ __volatile__("rdtsc");
}

// 4 higher bits of rand()
int generate_rand_high()
{
	return (rand() >> 16-4-1) & 0x0F;
}

// 4 lowers bits of rand()
int generate_rand_low()
{
	return rand() & 0x0F;
}

// AES
int generate_aes()
{
	static u32 Kx[NK], Kex[NB*(NR + 1)], Px[NB]; // pour l'AES
	static int is_first_call = 1;

	if (is_first_call)
	{
		init_rand(Kx, Px, NK, NB, 45);
		is_first_call = 0;
	}

	KeyExpansion(Kex, Kx);	// AES : sous-clefs
	// Initialisation de la clé et du plaintext pour l'AES 
	return AES(Px, Kex); // AES	
}

// Mersenne-Twister
int generate_twister()
{
	struct mt19937p mt;
	int tmp = rand();
	sgenrand(time(NULL) + tmp, &mt);
	return genrand(&mt);
}

int generate_neumann()
{
	static word16 x = 1111; // nombre entre 1000 et 9999 pour Von Neumann
	return Von_Neumann(&x); // Von Neumann
}

// Forward declarations
int* GenerateRandomValues(unsigned int n, const char* name, int(*random_generator)(void));
double p_value(int* values, size_t value_count, unsigned int bit_count);
double Frequency(int* values, size_t value_count, unsigned int bit_count);

int main()
{
	srand(rdtsc());

	// Génération des tableaux de valeurs aléatoires
	int* von_values = GenerateRandomValues(RANDOM_VALUE_COUNT, "../_von_neumann.csv", generate_neumann);
	int* aes_values = GenerateRandomValues(RANDOM_VALUE_COUNT, "../_aes.csv", generate_aes);
	int* twi_values = GenerateRandomValues(RANDOM_VALUE_COUNT, "../_twister.csv", generate_twister);
	int* high_values = GenerateRandomValues(RANDOM_VALUE_COUNT, "../_rand_high.csv", generate_rand_high);
	int* low_values = GenerateRandomValues(RANDOM_VALUE_COUNT, "../_rand_low.csv", generate_rand_low);
	int* rand_values = GenerateRandomValues(RANDOM_VALUE_COUNT, "../_rand.csv", rand);

	// Calcul et affichage de la P-valeur des différentes méthodes de génération de vaes aléatoires
	//printf("- Generation de nombres aleatoires -\n");
	printf("pvalue, frequency\n");
	printf("rand(), %f, %f \n", p_value(rand_values, RANDOM_VALUE_COUNT, 16 - 1), Frequency(rand_values, RANDOM_VALUE_COUNT, 16 - 1));
	printf("Von Neumann, %f, %f\n", p_value(von_values, RANDOM_VALUE_COUNT, 13), Frequency(von_values, RANDOM_VALUE_COUNT, 13)); // de 0 à 9999 ? sur 14 ou 13 bits ?
	printf("Mersenne-Twister, %f, %f\n", p_value(twi_values, RANDOM_VALUE_COUNT, 32), Frequency(twi_values, RANDOM_VALUE_COUNT, 32));
	printf("AES, %f, %f\n", p_value(aes_values, RANDOM_VALUE_COUNT, 32), Frequency(aes_values, RANDOM_VALUE_COUNT, 32));

	// Libération de la mémoire
	free(von_values);
	free(aes_values);
	free(twi_values);
	free(high_values);
	free(low_values);
	free(rand_values);

	return 0;
}

// Generates 'n' random values from given 'random_generator' and store them into a file named 'name'
int* GenerateRandomValues(unsigned int n, const char* name, int(*random_generator)(void))
{
	FILE* fichier = fopen(name, "w");
	int* values = malloc(sizeof(int)*n);

	if (fichier != NULL)
	{
		fprintf(fichier, "values\n");
		for (unsigned int i = 0; i < n; ++i)
		{
			values[i] = random_generator();
			fprintf(fichier, "%d\n", values[i]);
		}

		fclose(fichier);
	}

	return values;
}

double Frequency(int* values, size_t value_count, unsigned int bit_count)
{
	int sum = 0;

	for (size_t i = 0; i < value_count; i++)
	{
		for (unsigned long long mask = 1; mask < pow(2, bit_count); mask *= 2)
			sum += ((values[i] & mask) != 0) ? 1 : -1;
	}

	return abs(sum) / sqrt(value_count*bit_count);
}

// Finds the p_value of 'value_count' integers encoded using 'bit_count' bits
double p_value(int* values, size_t value_count, unsigned int bit_count)
{
	return erfc(Frequency(values, value_count, bit_count) / sqrt(2));
}

