#ifndef FILE_ATTENTE_H
#define FILE_ATTENTE_H

#include <stdlib.h>
#include <stdio.h>

#define ARRAY_MAX_SIZE 1000

typedef struct
{
	double arrivee[ARRAY_MAX_SIZE];
	size_t size_arrivee;
	double depart[ARRAY_MAX_SIZE];
	size_t size_depart;
} file_attente;

void init(file_attente* fa);
file_attente FileMM1(double lambda, double mu, double D);


#endif // FILE_ATTENTE_H