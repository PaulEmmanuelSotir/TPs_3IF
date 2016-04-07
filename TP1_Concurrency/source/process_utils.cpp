/*************************************************************************
			Process utils - aide à la manipulation de processus
			---------------------------------------------------
	debut   			 : 20/03/2016
	copyright            : (C) process_utils.cpp par B3330
	e-mail               : paul-emmanuel.sotir@insa-lyon.fr
*************************************************************************/

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <functional>
#ifndef _MSC_VER
#include <unistd.h>
#endif

//------------------------------------------------------ Include personnel
#include "process_utils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//----------------------------------------------------- Fonctions publique

pid_t fork(const std::function<void(void)>& code_fils, const std::function<void(pid_t)>& code_pere)
{
	pid_t fils_pid;

	if ((fils_pid = fork()) == 0)
		code_fils();
	else
		code_pere(fils_pid);

	return fils_pid;
}

