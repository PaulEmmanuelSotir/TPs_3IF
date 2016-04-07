/*************************************************************************
					Commande  -  module regroupant les commandes
					--------------------------------------------
	debut   			 : 18/03/2016
	copyright            : (C) commande.cpp par B3330
	e-mail               : paul-emmanuel.sotir@insa-lyon.fr
*************************************************************************/

//---------- Realisation du module <COMMANDE> (fichier commande.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "commande.h"
#include "clavier.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Commande(char code, unsigned int valeur)
{
	switch (code)
	{
	case 'e':
	case 'E':
		quit_clavier();
		break;
	case 'p':
	case 'P':
		// TODO: ajouter un prof
		break;
	case 'a':
	case 'A':
		// TODO: ajouter un autre
		break;
	case 's':
	case 'S':
		// TODO: sortir voiture
		break;
	}
}

