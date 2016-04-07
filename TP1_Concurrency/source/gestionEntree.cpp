/*************************************************************************
			Gestion entree - tache gerant les barrieres d'entree
			----------------------------------------------------
	debut   			 : 18/03/2016
	copyright            : (C) gestionEntree.cpp par B3330
	e-mail               : paul-emmanuel.sotir@insa-lyon.fr
*************************************************************************/

//-- Realisaion de la tache <GESTION_ENTRE> (fichier gestionEntree.cpp) --

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#ifndef _MSC_VER
#include <unistd.h>
#endif

//------------------------------------------------------ Include personnel
#include "gestionEntree.h"
#include "process_utils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

static void PorteEntree()
{
	while(true)
	{
		
	}
}

//////////////////////////////////////////////////////////////////  PUBLIC
//----------------------------------------------------- Fonctions publique

pid_t ActiverPorteGB()
{
	return fork([]()
	{
		// Code du fils
		PorteEntree();
	});
}

pid_t ActiverPorteBPProfs()
{
	return fork([]()
	{
		// Code du fils
		PorteEntree();
	});
}

pid_t ActiverPorteBPAutres()
{
	return fork([]()
	{
		// Code du fils
		PorteEntree();
	});
}

