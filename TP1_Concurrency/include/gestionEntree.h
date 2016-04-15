/*************************************************************************
			Gestion entree - tache gerant les barrieres d'entree
			----------------------------------------------------
	debut   			 : 18/03/2016
	binome               : B3330
*************************************************************************/

//--- Interface du module <GESTION_ENTREE> (fichier gestionEntree.h) -----
#ifndef GESTION_ENTREE_H
#define GESTION_ENTREE_H

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <array>
#include "Outils.h"
#include "process_utils.h"

//------------------------------------------------------------------ Types
//! Type contenant les information nescessaires sur une voiture
//! Ce type est utilise sur de la memoire partagee.
struct car_info
{
	// Les constructeurs ne sont plus nescessaires en C++14 pour avoir des initilizer list + des valeurs par defaut
	car_info() = default;
	car_info(unsigned int num, TypeUsager type, time_t t)
		: car_number(num), user_type(type), heure_arrivee(t) { };
	volatile unsigned int car_number = 0U;
	volatile int user_type = AUCUN;
	volatile time_t heure_arrivee = 0;
};

//! Represente une requete d'un voiture voulant entrer dans le parking plein
//! Ce type est utilise sur de la memoire partagee.
struct request
{
	// Les constructeurs ne sont plus nescessaires en C++14 pour avoir des initilizer list + des valeurs par defaut
	request() = default;
	request(TypeUsager t, time_t h) : type(t), heure_requete(h) { };
	volatile TypeUsager type = AUCUN;
	volatile time_t heure_requete = 0;
};

//! Struture contenant le prochain id donne a une voiture et le nombre de
//! voitures dans le parking.
//! Ce type est utilise sur de la memoire partagee.
struct parking
{
	volatile unsigned int next_car_id = 1U;
	volatile unsigned int car_count = 0U;
	bool is_full() const { return car_count >= NB_PLACES; }
};

//! Ce type est utilise sur de la memoire partagee.
struct places
{ car_info places[NB_PLACES]; };

//! Ce type est utilisé sur de la memoire partagée.
struct waiting_cars
{ request waiting_fences[NB_BARRIERES_ENTREE]; };

//---------------------------------------------------- Fonctions publiques
//! Démare la tache gèrant la barrière identifiée par sont type (TypeBarriere)
//! Retourne le PID du processus fils ou -1 en cas d'echec.
pid_t ActiverPorte(TypeBarriere t);

#endif // GESTION_ENTREE_H
