#include "random_generation.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "mersenne_twister.h"
#include "von_neumann.h"
#include "aes.h"

//--------------------------------------------------------------------------- GENERATEURS ALEATOIRES

// 4 higher bits of rand()
int generate_rand_high()
{
	return (rand() >> (16 - 4 - 1)) & 0x0F;
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

// Von eumann
int generate_neumann()
{
	static word16 x = 1111; // nombre entre 1000 et 9999 pour Von Neumann
	return Von_Neumann(&x); // Von Neumann
}

//---------------------------------------------------------------------------------- generator_array

// Generates 'n' random values (of 'bit_count' used bits) from given 'random_generator' and store them 
// into a file named 'name' (returns data as a generator_array).
generator_array GenerateRandomValues(unsigned int n, unsigned int bit_count, const char* name, int(*random_generator)(void))
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
	generator_array data = { values, n, bit_count };
	return data;
}

int get_bit(generator_array* data, size_t index)
{
	size_t val_idx = index / data->bit_count;
	size_t bit_idx = index - val_idx * data->bit_count;
	int val = data->values[val_idx];

	return (val & (1 << bit_idx)) != 0 ? 1 : 0;
}

size_t size(generator_array* data)
{
	return data->bit_count * data->values_count;
}

void destroy(generator_array* data)
{
	free(data->values);
}
