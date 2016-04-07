/*************************************************************************
					Clavier  -  tache gerant l'entree clavier
					-----------------------------------------
	debut                : 18/03/2016
	copyright            : (C) clavier.cpp par B3330
	e-mail               : paul-emmanuel.sotir@insa-lyon.fr
*************************************************************************/

//---------- Realisation du module <CLAVIER> (fichier clavier.cpp) -------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <functional>

//------------------------------------------------------ Include personnel
#include "process_utils.h"
#include "clavier.h"
#include "Menu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

//!
pid_t activer_clavier()
{
	// Creation de la tache clavier
	return fork([]()
	{
		// Code du fils
		Menu();
	});
}

void quit_clavier()
{
	exit(0);
}
