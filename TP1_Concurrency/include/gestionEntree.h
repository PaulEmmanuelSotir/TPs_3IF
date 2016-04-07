/*************************************************************************
			Gestion entree - tache gerant les barrieres d'entree
			----------------------------------------------------
	debut   			 : 18/03/2016
	copyright            : (C) gestionEntree.h par B3330
	e-mail               : paul-emmanuel.sotir@insa-lyon.fr
*************************************************************************/

//--- Interface du module <GESTION_ENTREE> (fichier gestionEntree.h) -----
#ifndef GESTION_ENTREE_H
#define GESTION_ENTREE_H

//------------------------------------------------------------------------
// Role de la tache gestion entree
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "msvc_utils.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
pid_t ActiverPorteGB();
pid_t ActiverPorteBPProfs();
pid_t ActiverPorteBPAutres();

#endif // GESTION_ENTREE_H
