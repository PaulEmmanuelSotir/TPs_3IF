/*************************************************************************
			Gestion sortie - tache gerant les barrieres de sortie
			-----------------------------------------------------
	debut   			 : 18/03/2016
	binome               : B3330
*************************************************************************/

//-- Interface de la tache <GESTION_SORTIE> (fichier gestionSortie.h) ----
#ifndef GESTION_SORTIE_H
#define GESTION_SORTIE_H

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "process_utils.h"
#include "gestionEntree.h"

//---------------------------------------------------- Fonctions publiques

//! Demare la tache gestionSortie pour permettre aux voitures de sortir
//! Retourne le PID du processus fils ou -1 en cas d'echec.
pid_t ActiverPorteSortie();

#endif // GESTION_SORTIE_H
