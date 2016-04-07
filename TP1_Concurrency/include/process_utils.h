/*************************************************************************
			Process utils - aide à la manipulation de processus
			---------------------------------------------------
	debut   			 : 20/03/2016
	copyright            : (C) process_utils.cpp par B3330
	e-mail               : paul-emmanuel.sotir@insa-lyon.fr
*************************************************************************/

#ifndef PROCESS_UTILS_H
#define PROCESS_UTILS_H

//------------------------------------------------------------------------
// Role du module process utils
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <functional>
#include "sys/types.h"
#include "msvc_utils.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

using signal_t = int;

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
//! 
pid_t fork(const std::function<void(void)>& code_fils, const std::function<void(pid_t)>& code_pere = [](pid_t) {});


#endif // PROCESS_UTILS_H
