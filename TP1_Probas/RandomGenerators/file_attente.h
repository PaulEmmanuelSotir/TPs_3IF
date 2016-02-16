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


typedef struct
{
	double temps[ARRAY_MAX_SIZE];
	int nombre[ARRAY_MAX_SIZE];
	size_t size;
} evolution;

void init(file_attente* fa);
void init_evol(evolution* evol);

// Création de la file d'attente MM1 en fonction des paramètres des deux distributions exponentielles et du temps D
file_attente FileMM1(double lambda, double mu, double D);
// Création de la file d'attente MMN en fonction des paramètres des deux distributions exponentielles et du temps D
file_attente FileMMN(double lambda, double mu, double D, size_t n);
// Calcul de l'évolution de la file d'attente
evolution get_evolution(file_attente* fa, double D);

// Serialisation de la file d'attente
void fprint(file_attente* data, const char* filename);
// Sérialisation de l'évolution de la file d'attente
void fprint_evol(evolution* data, const char* filename);

// Temps moyen de présence d'un client (attente + service)
double get_time_mean(file_attente* fa, evolution* evol);
// Nombre moyen de clients dans le système
double get_number_mean(evolution* evol);

#endif // FILE_ATTENTE_H