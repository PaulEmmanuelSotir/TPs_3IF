/*************************************************************************
				Main - Tache mere de l'application
				----------------------------------
	debut   			 : 18/03/2016
	binome               : B3330
*************************************************************************/

/////////////////////////////////////////////////////////////////  INCLUDE
//------------------------------------------------------- Include systeme
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/wait.h> 
#include <sys/types.h>

//------------------------------------------------------ Include personnel
#include "process_utils.h"
#include "gestionSortie.h"
#include "gestionEntree.h"
#include "clavier.h"
#include "Outils.h"
#include "Heure.h"

///////////////////////////////////////////////////////////////////  PRIVE
namespace
{
	//-------------------------------------------------------------- Types
	//! Structure regroupant les pid des processus fils et les outils de 
	//! communication entre processus.
	struct
	{
		pid_t heure_pid = -1;
		pid_t clavier_pid = -1;
		pid_t porte_gb_pid = -1;
		pid_t porte_bp_autres_pid = -1;
		pid_t porte_bp_profs_pid = -1;
		pid_t porte_sortie_pid = -1;

		ipc_id_t parking_state_id = 0;
		ipc_id_t waiters_id = 0;
		ipc_id_t parking_places_id = 0;
		ipc_id_t entrance_mqid = -1;
		ipc_id_t exit_mqid = -1;
		ipc_id_t semaphores_id = -1;
	} ressources;

	//-------------------------------------------------- Fonctions privees
	//! Termine la tache mère et ses taches filles
	void quit_app()
	{
		// Fonction lambda utilisée pour terminer une tache
		auto kill_task = [](pid_t task, const std::string& message, signal_t sig = SIGUSR2)
		{
			if (task >= 0)
			{
				kill(task, sig);
				Effacer(MESSAGE);
				Afficher(MESSAGE, message.data());
				waitpid(task, nullptr, 0);
			}
		};

		// Delete application tasks
		kill_task(ressources.porte_bp_profs_pid, "FIN porte bp profs");
		kill_task(ressources.porte_bp_autres_pid, "FIN porte bp autres");
		kill_task(ressources.porte_gb_pid, "FIN porte gb");
		kill_task(ressources.porte_sortie_pid, "FIN porte sortie");
		kill_task(ressources.clavier_pid, "FIN clavier");
		kill_task(ressources.heure_pid, "FIN heure");

		// Suppression des message queues
		delete_message_queue(ressources.entrance_mqid);
		delete_message_queue(ressources.exit_mqid);

		// Suppression de la memoire partagée
		delete_shared_memory(ressources.parking_state_id);
		delete_shared_memory(ressources.waiters_id);
		delete_shared_memory(ressources.parking_places_id);

		// Suppression des semaphores
		semctl(ressources.semaphores_id, 0, IPC_RMID, 0);

		// On retire le handler deu signal SIGCHLD
		unsubscribe_handler<SIGCHLD>();

		TerminerApplication();
		exit(EXIT_SUCCESS);
	}

	//! Crée les taches filles et les ressources pour l'ipc
	void init()
	{
		// Fonction lambda utilisée pour quitter en cas d'erreur
		auto quit_if_failed = [](bool condition) {
			if (!condition)
				quit_app();
		};

		InitialiserApplication(XTERM);

		// On ajoute un handler pour le signal SIGCHLD indiquant qu'une tache fille s'est terminée
		quit_if_failed(handle<SIGCHLD>([](signal_t sig) {
			quit_app(); // On quitte proprement
		}));

		// Création de la 'message queue' utilisée pour communiquer entre le clavier et les barrières
		quit_if_failed(create_message_queue(ressources.entrance_mqid, 1));

		// Création de la 'message queue' utilisée pour communiquer entre le clavier et la sortie
		quit_if_failed(create_message_queue(ressources.exit_mqid, 2));

		// Création de la mémoire partagée (utilisée par les barrieres)
		ressources.parking_state_id = create_detached_shared_mem<parking>(4);
		quit_if_failed(ressources.parking_state_id != -1);
		ressources.waiters_id = create_detached_shared_mem<waiting_cars>(5);
		quit_if_failed(ressources.waiters_id != -1);
		ressources.parking_places_id = create_detached_shared_mem<places>(6);
		quit_if_failed(ressources.parking_places_id != -1);

		// Creation des semaphores pour l'acces a la memoire partagée et l'attente au niveau des barrières en cas de parking plein
		ressources.semaphores_id = semget(ftok(".", 3), 4U, IPC_CREAT | 0600);
		quit_if_failed(ressources.semaphores_id != -1);
		quit_if_failed(semctl(ressources.semaphores_id, 0, SETVAL, 1) != -1);
		quit_if_failed(semctl(ressources.semaphores_id, PROF_BLAISE_PASCAL, SETVAL, 0) != -1);
		quit_if_failed(semctl(ressources.semaphores_id, AUTRE_BLAISE_PASCAL, SETVAL, 0) != -1);
		quit_if_failed(semctl(ressources.semaphores_id, ENTREE_GASTON_BERGER, SETVAL, 0) != -1);

		// Creation de la tache 'heure'
		ressources.heure_pid = ActiverHeure();
		quit_if_failed(ressources.heure_pid != -1);

		// Creation de la tache 'clavier'
		ressources.clavier_pid = activer_clavier();
		quit_if_failed(ressources.clavier_pid != -1);

		// Creation des taches 'gestionEntree' pour chaque barrieres a l'entree
		ressources.porte_gb_pid = ActiverPorte(ENTREE_GASTON_BERGER);
		quit_if_failed(ressources.porte_gb_pid != -1);
		ressources.porte_bp_profs_pid = ActiverPorte(PROF_BLAISE_PASCAL);
		quit_if_failed(ressources.porte_bp_profs_pid != -1);
		ressources.porte_bp_autres_pid = ActiverPorte(AUTRE_BLAISE_PASCAL);
		quit_if_failed(ressources.porte_bp_autres_pid != -1);

		// Creation de la tache 'gestionSortie'
		ressources.porte_sortie_pid = ActiverPorteSortie();
		quit_if_failed(ressources.porte_sortie_pid != -1);
	}
}

//////////////////////////////////////////////////////////////////  PUBLIC
//----------------------------------------------------- Fonctions publique
//! Tache mère
int main(int argc, char* argv[])
{
	// Creation des taches filles et des ressources pour l'ipc
	init();

	// Attente de la fin de la tache clavier
	waitpid(ressources.clavier_pid, nullptr, 0);

	// Destruction de la tache mere
	quit_app();
}
