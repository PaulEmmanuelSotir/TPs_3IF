/*************************************************************************
			Gestion sortie - tache gerant les barrieres de sortie
			-----------------------------------------------------
	debut   			 : 18/03/2016
	copyright            : (C) gestionEntree.cpp par B3330
	e-mail               : paul-emmanuel.sotir@insa-lyon.fr
*************************************************************************/

//- Realisaion de la tache <GESTION_SORTIE> (fichier gestionSortie.cpp) --

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#ifndef _MSC_VER
#include <unistd.h>
#endif

//------------------------------------------------------ Include personnel
#include "gestionSortie.h"
#include "process_utils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

static void PorteSortie()
{
	while(true)
	{
		
	}
}

//////////////////////////////////////////////////////////////////  PUBLIC
//----------------------------------------------------- Fonctions publique

pid_t ActiverPorteSortie()
{
	return fork([]()
	{
		// Code du fils
		PorteSortie();
	});
}


