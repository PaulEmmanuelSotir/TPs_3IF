#ifndef RANDOM_GENERATION_H
#define RANDOM_GENERATION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define RANDOM_VALUE_COUNT 1024

// 4 higher bits of rand()
int generate_rand_high();
// 4 lowers bits of rand()
int generate_rand_low();
// AES
int generate_aes();
// Mersenne-Twister
int generate_twister();
// Von eumann
int generate_neumann();

// Structure simplifiant la manipulation de la génération d'un tableau de valeurs aléatoires
typedef struct
{
	// Tableau des valeures
	int* values;
	// Nombre de valeures
	size_t values_count;
	// Nombre de bits pris en compte dans chaque valeures
	unsigned int bit_count;
} generator_array;

int get_bit(generator_array* data, size_t index);
size_t size(generator_array* data);
void destroy(generator_array* data);

// Generates 'n' random values (of 'bit_count' used bits) from given 'random_generator' and store them 
// into a file named 'name' (returns data as a generator_array).
generator_array GenerateRandomValues(unsigned int n, unsigned int bit_count, const char* name, int(*random_generator)(void));

#endif // RANDOM_GENERATION_H