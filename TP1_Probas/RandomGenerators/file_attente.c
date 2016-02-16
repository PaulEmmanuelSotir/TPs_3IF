#include "file_attente.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "lois_distributions.h"

void init(file_attente* fa)
{
	memset(fa->arrivee, 0.0, sizeof(double)*ARRAY_MAX_SIZE);
	memset(fa->depart, 0.0, sizeof(double)*ARRAY_MAX_SIZE);
}

void init_evol(evolution* evol)
{
	memset(evol->nombre, 0.0, sizeof(int)*ARRAY_MAX_SIZE);
	memset(evol->temps, 0.0, sizeof(double)*ARRAY_MAX_SIZE);
}

// Création de la file d'attente en fonction des paramètres des deux distributions exponentielles et du temps D
file_attente FileMM1(double lambda, double mu, double D)
{
	file_attente fa;
	init(&fa);

	// Creation du tableau d'arrivée
	double t = Exponentielle(lambda);
	for (fa.size_arrivee = 0; 1; ++fa.size_arrivee)
	{
		t += Exponentielle(lambda);
		if (t > D)
			break;
		fa.arrivee[fa.size_arrivee] = t;
	}

	// Creation du tableau de départ
	double new_depart = fa.arrivee[0] + Exponentielle(mu);
	if (new_depart < D)
	{
		fa.depart[0] = new_depart;
		for (fa.size_depart = 1; fa.size_depart < fa.size_arrivee; ++fa.size_depart)
		{
			if (fa.depart[fa.size_depart - 1] <= fa.arrivee[fa.size_depart])
				new_depart = fa.arrivee[fa.size_depart] + Exponentielle(lambda);
			else
				new_depart = fa.depart[fa.size_depart - 1] + Exponentielle(lambda);

			if (new_depart > D)
				break;
			fa.depart[fa.size_depart] = new_depart;
		}
	}
	else
		fa.size_depart = 0;

	return fa;
}

file_attente FileMMN(double lambda, double mu, double D, size_t n)
{
	file_attente fa;
	init(&fa);

	// Creation du tableau d'arrivée (inchangé par rapport à MM1)
	double t = Exponentielle(lambda);
	for (fa.size_arrivee = 0; 1; ++fa.size_arrivee)
	{
		t += Exponentielle(lambda);
		if (t > D)
			break;
		fa.arrivee[fa.size_arrivee] = t;
	}

	// Creation du tableau de départ (ici intervient les chagements pusique l'on traite jusqu'a deux clients à la fois)
	double new_depart = fa.arrivee[0] + Exponentielle(mu);
	double* servers = (double*)malloc(sizeof(double) * n); // contien l'heur j'usqu'a laquelle chaque serveur est occupé
	memset(servers, 0.0, sizeof(double) * n);

	if (new_depart < D)
	{
		fa.depart[0] = new_depart;
		for (fa.size_depart = 1; fa.size_depart < fa.size_arrivee; ++fa.size_depart)
		{
			double min_server_free_time = D+1;
			int started = 0;
			for (size_t server_idx = 0; server_idx < n; ++server_idx)
			{
				// On met à jour le moment le plus tôt où un server est libre
				min_server_free_time = servers[server_idx] < min_server_free_time ? servers[server_idx] : min_server_free_time;
				
				// On vérifie si le serveur n'est pas occupé
				if(fa.arrivee[fa.size_depart] >= servers[server_idx])
				{
					// On traite immédiatement la requette
					new_depart = fa.arrivee[fa.size_depart] + Exponentielle(lambda);
					servers[server_idx] = new_depart;
					started = 1;
				}
			}

			// Si tous les serveurs sont occupés, ont retarde la tache pour être traité par le serveur qui auras fini le plus tôt
			if(started == 0)
				new_depart = min_server_free_time + Exponentielle(lambda);

			if (new_depart > D)
				break;
			fa.depart[fa.size_depart] = new_depart;
		}
	}
	else
		fa.size_depart = 0;

	free(servers);

	return fa;	
}

// Calcul de l'évolution de la file d'attente
evolution get_evolution(file_attente* fa, double D)
{
	evolution evol;
	init_evol(&evol);
	evol.size = 1;

	size_t arrivee_count = 0, depart_count = 0;
	size_t arrivee_idx = 0, depart_idx = 0;
	double t = 0.0;
	while (arrivee_idx < fa->size_arrivee)
	{
		// On se place soit sur un temps d'arrivée ou de départ (mise à jour pour chaque temps présent dans la file)
		if (fa->arrivee[arrivee_idx] <= fa->depart[depart_idx] || fa->depart[depart_idx] == 0)
		{
			evol.temps[1 + depart_idx + arrivee_idx] = t = fa->arrivee[arrivee_idx];
			++arrivee_idx;
		}
		else
		{
			evol.temps[1 + depart_idx + arrivee_idx] = t = fa->depart[depart_idx];
			++depart_idx;
		}

		// Recherche du nombre d'arrivées avant t
		size_t idx;
		for (idx = arrivee_count; idx < fa->size_arrivee; ++idx)
			if (fa->arrivee[idx] > t)
				break;
		arrivee_count = idx;

		// Recherche du nombre de départs avant t
		for (idx = depart_count; idx < fa->size_depart; ++idx)
			if (fa->depart[idx] > t)
				break;
		depart_count = idx;

		evol.nombre[depart_idx + arrivee_idx] = arrivee_count - depart_count;
		++evol.size;
	}

	evol.temps[evol.size] = D;
	evol.nombre[evol.size] = evol.size > 0 ? evol.nombre[evol.size-1] : 0;
	++evol.size;

	return evol;
}

// Serialisation de la file d'attente
void fprint(file_attente* data, const char* filename)
{
	// Ouverture du fichier CSV
	FILE* fichier = fopen(filename, "w");
	if (fichier != NULL)
	{
		fprintf(fichier, "arrivee, depart \n");

		for (size_t i = 0; i < data->size_arrivee || i < data->size_depart; ++i)
			fprintf(fichier, "%lf, %lf\n", data->arrivee[i], data->depart[i]);

		fclose(fichier);
	}
}

// Sérialisation de l'évolution de la file d'attente
void fprint_evol(evolution* data, const char* filename)
{
	// Ouverture du fichier CSV
	FILE* fichier = fopen(filename, "w");
	if (fichier != NULL)
	{
		fprintf(fichier, "t, nombre \n");

		for (size_t i = 0; i < data->size; ++i)
			fprintf(fichier, "%lf, %d\n", data->temps[i], data->nombre[i]);

		fclose(fichier);
	}
}

// Temps moyen de présence d'un client (attente + service)
double get_time_mean(file_attente* fa, evolution* evol)
{
	// Calcul du temps total de présence de tout les clients accumulé
	double sum = 0;
	double delta = 0;
	for (size_t i = 0; i < evol->size; ++i)
	{
		delta = i > 0 ? evol->temps[i] - evol->temps[i - 1] : evol->temps[i];
		sum += evol->nombre[i] * delta;
	}

	return sum / fa->size_arrivee; // On divise par le nombre de clients
}

// Nombre moyen de clients dans le système
double get_number_mean(evolution* evol)
{
	// Calcul du temps total de présence de tout les clients accumulé
	double sum = 0;
	double delta = 0;
	for (size_t i = 0; i < evol->size; ++i)
	{
		delta = i > 0 ? evol->temps[i] - evol->temps[i - 1] : evol->temps[i];
		sum += evol->nombre[i] * delta;
	}

	return sum / evol->temps[evol->size - 1]; // On divise par la durée totale
}
