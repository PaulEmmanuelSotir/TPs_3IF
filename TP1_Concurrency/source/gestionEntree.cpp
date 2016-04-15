/*************************************************************************
			Gestion entree - tache gerant les barrieres d'entree
			----------------------------------------------------
	debut   			 : 18/03/2016
	binome               : B3330
*************************************************************************/

//-- Realisaion de la tache <GESTION_ENTREE> (fichier gestionEntree.cpp) -

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <unordered_map>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include <utility>
#include <string>
#include <ctime>

//------------------------------------------------------ Include personnel
#include "gestionEntree.h"
#include "process_utils.h"
#include "clavier.h"
#include "Outils.h"

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
	std::unordered_map<pid_t, car_info> car_parking_tasks;

	//-------------------------------------------------- Fonctions privées
	void quit_entree()
	{
		// On retire les handlers des signaux SIGCHLD et SIGUSR2
		unsubscribe_handler<SIGCHLD, SIGUSR2>();

		// On quitte tout les processus garant des voitures
		for (const auto& parking_task : car_parking_tasks) {
			if (parking_task.first > 0)
			{
				kill(parking_task.first, SIGUSR2);
				waitpid(parking_task.first, nullptr, 0);
			}
		}

		// Detache 'parking_state' de la memoire partagée
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
pid_t ActiverPorte(TypeBarriere type)
{
	// Creation du processus fils
	return fork([type]()
	{
		// Fonction lambda aidant a quitter en cas d'erreur
		auto quit_if_failed = [](bool condition) {
			if (!condition)
				quit_entree();
		};

		// On ajoute un handler pour le signal SIGUSR2 indiquant que la tache doit se terminer
		quit_if_failed(handle<SIGUSR2>([](signal_t sig) { quit_entree(); }));

		// Ouverture de la message queue utilisée pour recevoir les voitures
		quit_if_failed(open_message_queue(car_message_queue_id, 1));

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

		// On ajoute un handler pour le signal SIGCHLD indiquant qu'une voiture s'est garée
		quit_if_failed(handle<SIGCHLD>([](signal_t sig)
		{
			int status;
			pid_t chld = waitpid(-1, &status, WNOHANG);
			if (chld > 0 && WIFEXITED(status))
			{
				// On affiche la place et on met à jour la memoire partagée
				auto car = car_parking_tasks[chld];
				auto place_num = WEXITSTATUS(status);

				lock(sem_id, 0, [&car, place_num]() {
					parking_places.data->places[place_num - 1] = car;
				});

				car_parking_tasks.erase(chld);
				AfficherPlace(WEXITSTATUS(status), (TypeUsager)car.user_type, car.car_number, car.heure_arrivee);
			}
		}));

		// Phase moteur
		while (true)
		{
			// On attend la reception d'un message de la tache clavier
			car_incomming_msg message;
			quit_if_failed(read_message(car_message_queue_id, type, message));

			DessinerVoitureBarriere(type, message.type_usager);
			AfficherRequete(type, message.type_usager, time(nullptr));

			bool is_full = false;
			unsigned int next_car_id = 0;
			do
			{
				quit_if_failed(lock(sem_id, 0, [&message, type, &is_full, &next_car_id]()
				{
					// On vérifie que le parking n'est pas (de nouveau) plein avant de laisser passer la voiture
					is_full = parking_state.data->is_full();
					if (!is_full) {
						next_car_id = parking_state.data->next_car_id++;
						parking_state.data->car_count++;
					}
					else
						waiting.data->waiting_fences[type - 1] = { message.type_usager, time(nullptr) };
				}));

				if (is_full)
					// On attend qu'une place se libère
					sem_pv(sem_id, type, -1);
			} while (is_full);

			lock(sem_id, 0, [type]() {
				waiting.data->waiting_fences[type - 1] = { AUCUN, 0 };
			});

			// La barrière s'ouvre et on gare la voiture
			pid_t garage_pid = GarerVoiture(type);
			quit_if_failed(garage_pid);
			car_parking_tasks.emplace(garage_pid, car_info{ next_car_id, message.type_usager, time(nullptr) });

			sleep(1); // Temps pour avancer...
			Effacer(static_cast<TypeZone>(REQUETE_R1 + type - 1));
		}
	});
}
