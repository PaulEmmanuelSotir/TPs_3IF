/*************************************************************************
			Gestion sortie - tache gerant les barrieres de sortie
			-----------------------------------------------------
	debut   			 : 18/03/2016
	binome               : B3330
*************************************************************************/

//- Realisaion de la tache <GESTION_SORTIE> (fichier gestionSortie.cpp) --

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <unordered_map>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <utility>
#include <string>
#include <ctime>

//------------------------------------------------------ Include personnel
#include "gestionSortie.h"
#include "gestionEntree.h"
#include "process_utils.h"
#include "clavier.h"

///////////////////////////////////////////////////////////////////  PRIVE
namespace
{
	//------------------------------------------------ Variables statiques
	//! On utilise des variables statiques plutot que automatiques pour qu'elles
	//! soient accessibles depuis les handlers de signaux car ce sont des lambdas 
	//! qui ne peuvent rien capturer de leur contexte pour qu'elles puissent être 
	//! castés en pointeur de fonction C.
	ipc_id_t car_message_queue_id;
	ipc_id_t sem_id;
	shared_mem<parking> parking_state;
	shared_mem<waiting_cars> waiting;
	shared_mem<places> parking_places;
	std::unordered_map<pid_t, car_info> car_exiting_tasks;

	//-------------------------------------------------- Fonctions privées
	//! Termine la tache Gestion sortie
	void quit_sortie()
	{
		// On retire les handlers des signaux SIGCHLD et SIGUSR2
		unsubscribe_handler<SIGCHLD, SIGUSR2>();

		// Termine toutes les taches filles de sortie de voiture
		for (const auto& task : car_exiting_tasks) {
			if (task.first > 0)
			{
				kill(task.first, SIGUSR2);
				waitpid(task.first, nullptr, 0);
			}
		}

		// Detache les memoires partagées
		detach_shared_memory(parking_state.data);
		detach_shared_memory(waiting.data);
		detach_shared_memory(parking_places.data);

		// On notifie la tache mère de la fin pour qu'elle quitte les autres taches
		kill(getppid(), SIGCHLD);

		exit(EXIT_SUCCESS);
	}
}

//////////////////////////////////////////////////////////////////  PUBLIC
//----------------------------------------------------- Fonctions publique

pid_t ActiverPorteSortie()
{
	// Creation du processus fils
	return fork([]()
	{
		// Fonction lambda aidant a quitter en cas d'erreur
		auto quit_if_failed = [](bool condition)
		{
			if (!condition)
				quit_sortie();
		};

		// On ajoute un handler pour le signal SIGUSR2 indiquant que la tache doit se terminer
		quit_if_failed(handle<SIGUSR2>([](signal_t sig) { quit_sortie(); }));

		// Ouverture de la message queue utilisée pour recevoir les demandes de sortie
		quit_if_failed(open_message_queue(car_message_queue_id, 2));

		// Récuperation des semaphores
		sem_id = semget(ftok(".", 3), 4U, 0600);
		quit_if_failed(sem_id != -1);

		// Ouvre les memoires partagées
		parking_state = get_shared_memory<parking>(4);
		quit_if_failed(parking_state.data != nullptr);
		waiting = get_shared_memory<waiting_cars>(5);
		quit_if_failed(waiting.data != nullptr);
		parking_places = get_shared_memory<places>(6);
		quit_if_failed(parking_places.data != nullptr);

		// On ajoute un handler pour le signal SIGCHLD indiquant qu'une voiture est sortie
		quit_if_failed(handle<SIGCHLD>([](signal_t sig)
		{
			// On affiche les information de sortie, on efface les informations de la place et on met à jour la memoire partagée
			int status;
			pid_t chld = waitpid(-1, &status, WNOHANG);
			if (chld > 0 && WIFEXITED(status))
			{
				auto car = car_exiting_tasks[chld];
				auto place_num = WEXITSTATUS(status);

				request req_prof, req_gb, req_autre;
				lock(sem_id, 0, [&car, place_num, &req_prof, &req_gb, &req_autre]() {
					// Met a jour le nombre de voitures dans le parking
					if (parking_state.data->car_count > 0)
						parking_state.data->car_count--;

					req_prof = waiting.data->waiting_fences[PROF_BLAISE_PASCAL - 1];
					req_gb = waiting.data->waiting_fences[ENTREE_GASTON_BERGER - 1];
					req_autre = waiting.data->waiting_fences[AUTRE_BLAISE_PASCAL - 1];
				});

				// Laisse entrer une voiture attendant à une barrière en prenant en compte les priorités
				if (req_prof.type != AUCUN && !(req_gb.type == PROF && req_gb.heure_requete < req_prof.heure_requete))
					sem_pv(sem_id, PROF_BLAISE_PASCAL, 1); // Ont débloque la barrière PROF_BLAISE_PASCAL
				else if (req_gb.type != AUCUN && (req_gb.type == PROF || !(req_autre.type != AUCUN && req_gb.type == AUTRE && req_autre.heure_requete < req_gb.heure_requete)))
					sem_pv(sem_id, ENTREE_GASTON_BERGER, 1); // Ont débloque la barrière ENTREE_GASTON_BERGER
				else if (req_autre.type != AUCUN)
					sem_pv(sem_id, AUTRE_BLAISE_PASCAL, 1); // Ont débloque la barrière AUTRE_BLAISE_PASCAL

				car_exiting_tasks.erase(chld);
				Effacer(static_cast<TypeZone>(ETAT_P1 + place_num - 1));
				AfficherSortie((TypeUsager)car.user_type, car.car_number, car.heure_arrivee, time(nullptr));
			}
		}));

		// Phase moteur
		while (true)
		{
			// On attend la reception d'un message issu de la tache clavier
			car_exit_msg message;
			quit_if_failed(read_message(car_message_queue_id, 0, message));

			// On recupère les informations a la place spécifiée dans la memoire partagée
			car_info car;
			quit_if_failed(lock(sem_id, 0, [&car, &message]() {
				car = parking_places.data->places[message.place_num - 1];
				parking_places.data->places[message.place_num - 1] = { 0, AUCUN, 0 };
			}));

			// On sort la voiture si une voiture occupe la place spécifiée
			pid_t child_pid = SortirVoiture(message.place_num);
			car_exiting_tasks.emplace(child_pid, car);
		}
	});
}
