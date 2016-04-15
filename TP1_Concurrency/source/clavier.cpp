/*************************************************************************
					Clavier  -  tache gerant l'entree clavier
					-----------------------------------------
	debut                : 18/03/2016
	binome               : B3330
*************************************************************************/

//---------- Realisation du module <CLAVIER> (fichier clavier.cpp) -------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <string>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <functional>
#include <sys/types.h>

//------------------------------------------------------ Include personnel
#include "process_utils.h"
#include "clavier.h"
#include "Outils.h"
#include "Menu.h"

///////////////////////////////////////////////////////////////////  PRIVE
namespace
{
	//------------------------------------------------ Variables statiques
	static ipc_id_t incomming_car_mq_id;
	static ipc_id_t car_exit_mq_id;

	//-------------------------------------------------- Fonctions privees
	//! Termine la tache gèrant l'interface console
	void quit_clavier()
	{
		// On retire le handler du signal SIGUSR2
		unsubscribe_handler<SIGUSR2>();

		// On notifie la tache mère de la fin pour qu'elle quitte les autres taches
		kill(getppid(), SIGCHLD);

		exit(EXIT_SUCCESS);
	}
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
pid_t activer_clavier()
{
	// Creation de la tache clavier
	return fork([]()
	{
		// On ajoute un handler pour le signal SIGUSR2 indiquant que la tache doit se terminer
		if (!(handle<SIGUSR2>([](signal_t sig) { quit_clavier(); })))
			quit_clavier();

		// Ouverture de la 'message queue' utilisée pour communiquer avec les taches des barrières
		if (!open_message_queue(incomming_car_mq_id, 1))
			quit_clavier();

		// Ouverture de la 'message queue' utilisée pour communiquer avec la tache de sortie
		if (!open_message_queue(car_exit_mq_id, 2))
			quit_clavier();

		// Execute la phase moteur (interface console)
		while (true)
			Menu();
	});
}

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
		// On notifie la tache gerant la barriere de l'arrivee de la voiture
		if (!send_message(incomming_car_mq_id, car_incomming_msg{ (valeur == 1 ? PROF_BLAISE_PASCAL : ENTREE_GASTON_BERGER), PROF }))
			quit_clavier();
		break;
	case 'a':
	case 'A':
		// On notifie la tache gerant la barriere de l'arrivee de la voiture
		if (!send_message(incomming_car_mq_id, car_incomming_msg{ (valeur == 1 ? AUTRE_BLAISE_PASCAL : ENTREE_GASTON_BERGER), AUTRE }))
			quit_clavier();
		break;
	case 's':
	case 'S':
		// On notifie la tache gerant la sortie qu'une place doit être liberée (si il y a une voiture)
		if (!send_message(car_exit_mq_id, car_exit_msg{ valeur }))
			quit_clavier();
		break;
	}
}
