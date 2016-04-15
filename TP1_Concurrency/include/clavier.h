/*************************************************************************
					Clavier  -  tache gerant l'entree clavier
					-----------------------------------------
	debut				 : 18/03/2016
	binome               : B3330
*************************************************************************/

//---------- Interface du module <CLAVIER> (fichier clavier.h) -----------
#ifndef CLAVIER_H
#define CLAVIER_H

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisees
#include <sys/types.h>
#include <stdlib.h>
#include "Outils.h"

//------------------------------------------------------------------ Types
//! Structure utilisee par la message queue entre le clavier et les barrieres
struct car_incomming_msg
{
	long barriere_type;
	TypeUsager type_usager;
};

//! Structure utilisee par la message queue entre le clavier et la sortie
struct car_exit_msg
{
	long place_num;
};

//---------------------------------------------------- Fonctions publiques
//! Démare la tache gerant l'interface console
//! Retourne le PID du processus fils ou -1 en cas d'echec.
pid_t activer_clavier();

//! Gere les commandes déclanchées par le menu
void Commande(char code, unsigned int valeur);

#endif // CLAVIER_H

