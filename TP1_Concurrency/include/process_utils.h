/*************************************************************************
			Process utils - aide � la manipulation de processus
			---------------------------------------------------
	debut   			 : 20/03/2016
	binome               : B3330
*************************************************************************/

#ifndef PROCESS_UTILS_H
#define PROCESS_UTILS_H

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------- Interfaces utilis�es
#include <array>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <algorithm>
#include <functional>
#include <sys/types.h>

//----------------------------------------------------------------- Types
using signal_t = int;
using handler_t = void(*)(signal_t);
using sa_falg_t = int;
using ipc_id_t = int;

template<typename T>
struct shared_mem
{
	ipc_id_t id;
	T* data;
};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

//! Permet de creer un processus fils executant la fonction 'code_fils'.
//! Le parametre optionnel 'code_pere' permet de specifier du code specifique
//! au processus pere (avec pour parametre le pid du processus fils).
//! La fonction retourne le pid du processus fils.
pid_t fork(const std::function<void(void)>& code_fils, const std::function<void(pid_t)>& code_pere = [](pid_t) {});

//! Permet de gerer la reception de signaux. Les signaux qui seront geres
//! sont specifies sous la forme d'arguments template (variadic template).
//! La reception d'un des signaux specifies declanchera l'appel de la 
//! donnee en parametre 'handler'.
//! Le parametre optionnel 'flags' permet de specifier les flags qui 
//! seront donnes aux appels a 'sigaction'.
//! La fonction retourne true si tout les handlers pu etre inscrit à un signal.
//!	Exemple pour gerer les signaux SIGUSR1 et SIGINT :
//!		bool success = handle<SIGUSR1, SIGINT>([](signal_t sig)
//!		{ 
//!			/* code a executer lors de la reception d'un signal */ 
//!		});
template<signal_t... signals>
bool handle(handler_t handler, sa_falg_t falgs = SA_RESTART)
{
	if (handler != nullptr)
	{
		struct sigaction action;
		action.sa_handler = handler;
		sigemptyset(&action.sa_mask);
		action.sa_flags = falgs;

		// On execute sigaction pour recouvrir chaque signals en recuperant la valeur retournee
		std::array<int, sizeof...(signals)> return_codes{{ sigaction(signals, &action, nullptr)... }};

		// On verifie si des appels a sigaction on retournes '-1' (erreur)
		if (std::find(std::begin(return_codes), std::end(return_codes), -1) != std::end(return_codes)) // C++ 14: cbegin, cend
			//TODO: lancer une exception avec plus de details qu'un booleen et annuler tout les handlers des autre signaux
			return false;
		return true;
	}
	return false;
}

//! Permet de remettre le comportement par defaut à la reception des signaux 'signals...'.
//! Les signaux concernés sont specifies sous la forme d'arguments template (variadic template).
//! La fonction retourne true si tout les signaux ont été desinscrits.
template<signal_t... signals>
bool unsubscribe_handler()
{
	// Sigaction permettant de remettre le comportement par defaut
	struct sigaction unsub_action;
	unsub_action.sa_handler = SIG_DFL;
	sigemptyset(&unsub_action.sa_mask);
	unsub_action.sa_flags = 0;

	// On execute sigaction pour chaque signal donné en paramètre template
	std::array<int, sizeof...(signals)> return_codes{{ sigaction(signals, &unsub_action, nullptr)... }};

	// On verifie si des appels à sigaction on retournés '-1' (erreur)
	if (std::find(std::begin(return_codes), std::end(return_codes), -1) != std::end(return_codes)) // C++ 14: cbegin, cend
		//TODO: lancer une exception avec plus de details qu'un booleen et annuler tout les handlers des autre signaux
		return false;
	return true;
}

//! Envoie un message sur la 'message queue' dont l'id est donne en parametre.
//! Le type 'Buffer' est le type du message envoye devant etre conigue et contenir
//! un attribut 'long mtype' identifiant le type du message.
template<typename Buffer>
bool send_message(ipc_id_t msqid, const Buffer& message)
{
	return msgsnd(msqid, &message, sizeof(message) - sizeof(long), 0) != -1;
}

//! Recoit un message issu de la 'message queue' dont l'id est donne en parametre.
//! Le message recut est ecrit dans 'qbuf'.
//! Les messages recus sont filtres en fonction de leur types (parametre 'type').
//! Si la lecture a echouee, la fonction renvoie 'false'.
//! Un appel a cette fonction est bloquant (appel systeme bloquant).
template<typename Buffer>
bool read_message(ipc_id_t msqid, long type, Buffer& qbuf)
{
	int rslt = 0;
	do
	{
		rslt = msgrcv(msqid, &qbuf, sizeof(Buffer) - sizeof(long), type, 0);
	} while (rslt == -1 && errno == EINTR);
	return rslt >= 0;
}

//! Ouvre une 'message queue' dont l'id sera donne dans 'msquid'.
//! La message queue est identifiee par les parametres 'id' et 'path' permettant
//! de creer une cle (ftok).
//! Le parametre 'permission' permet de specifier les autorisation d'acces a la
//! 'message queue' (600 par defaut).
bool open_message_queue(ipc_id_t& msqid, int id, int permission = 0600, std::string path = std::string("."));

//! Crée une 'message queue' dont l'id sera donne dans 'msquid'.
//! La message queue est identifiee par les parametres 'id' et 'path' permettant
//! de creer une cle (ftok).
//! Le parametre 'permission' permet de specifier les autorisation d'acces a la
//! 'message queue' (600 par defaut).
//! Le parametre optionnel 'fail_if_exist' permet de choisir si la creation doit 
//! echouer si la message_queue existe deja ('false' par defaut).
bool create_message_queue(ipc_id_t& msqid, int id, int permission = 0600, std::string path = std::string("."), bool fail_if_exist = false);

//! Supprime la 'message_queue' dont l'id est donne en parametre.
//! Retourne 'true' si la suppression a bien eut lieu.
bool delete_message_queue(ipc_id_t msqid);

namespace
{
	template<typename T>
	shared_mem<T> get_or_create_shared_memory(ipc_id_t id, int permisssion, std::string path, bool fail_if_exist, bool create, bool attach = true)
	{
		// Cree une cle identifiant la memoire partagee
		key_t key = ftok(path.data(), id);
		if (key == -1)
			return{ -1, nullptr };

		// Cree ou ouvre la memoire partagee
		int flags = permisssion;
		if (create)
			flags |= IPC_CREAT;
		if (fail_if_exist)
			flags |= IPC_EXCL;
		auto shmid = shmget(key, sizeof(T), flags);
		if (shmid == -1)
			return{ -1, nullptr };

		if (attach)
		{
			// Recupere un pointeur vers la memoire partagee
			T* data = reinterpret_cast<T*>(shmat(shmid, nullptr, 0));
			if (data == reinterpret_cast<T*>(-1))
				return{ -1, nullptr };

			// Execute le constructeur du type 'T' a l'adresse allouee
			if (create)
				new (data) T();

			return{ shmid, data };
		}
		return{ shmid, nullptr };
	}
}

//! Ouvre une memoire partagée pour un objet de type 'T'.
//! La memoire partagée est identifiee par les parametres 'id' et 'path' permettant
//! de creer une cle (ftok).
//! Le parametre 'permission' permet de specifier les autorisation d'acces a la
//! memoire partagée (600 par defaut).
//! Le type 'T' doit disposer d'un constructeur par defaut.
template<typename T>
shared_mem<T> get_shared_memory(ipc_id_t id, int permisssion = 0600, std::string path = ".")
{
	return get_or_create_shared_memory<T>(id, permisssion, path, false, false);
}

//! Crée une memoire partagée pour un objet de type 'T'.
//! La memoire partagée est identifiee par les parametres 'id' et 'path' permettant
//! de creer une cle (ftok).
//! Le parametre 'permission' permet de specifier les autorisation d'acces a la
//! memoire partagée (600 par defaut).
//! Le parametre optionnel 'fail_if_exist' permet de choisir si la creation doit 
//! echouer si la memoire partagée existe deja ('false' par defaut).
//! Le type 'T' doit disposer d'un constructeur par defaut.
template<typename T>
shared_mem<T> create_shared_memory(ipc_id_t id, int permisssion = 0600, std::string path = ".", bool fail_if_exist = false)
{
	return get_or_create_shared_memory<T>(id, permisssion, path, fail_if_exist, true);
}

//! Detache l'objet de type 'T' de la mémoire partagée
//! Retourne 'true' si l'operation a eut lieu sans erreurs.
template<typename T>
bool detach_shared_memory(T& shared_data)
{
	return (shmdt(&shared_data) != -1);
}

//! Crée une memoire partagée pour un objet de type 'T' sans l'attacher au processus courant.
//! La memoire partagée est identifiee par les parametres 'id' et 'path' permettant
//! de creer une cle (ftok).
//! Le parametre 'permission' permet de specifier les autorisation d'acces a la
//! memoire partagée (600 par defaut).
//! Le parametre optionnel 'fail_if_exist' permet de choisir si la creation doit 
//! echouer si la memoire partagée existe deja ('false' par defaut).
//! Le type 'T' doit disposer d'un constructeur par defaut.
//! Retourne l'id de la mémoire partagée ou -1 en cas d'erreur 
template<typename T>
ipc_id_t create_detached_shared_mem(ipc_id_t id, int permisssion = 0600, std::string path = ".", bool fail_if_exist = false)
{
	auto memory = get_or_create_shared_memory<T>(id, permisssion, path, fail_if_exist, true, false);
	return memory.id;
}

//! Détruit la mémoire partagée identifiée par sont id donné en paramètre.
//! Retourne 'true' si la suppression a bien eut lieu.
bool delete_shared_memory(ipc_id_t id);

//! Ajoute la valeur 'num_to_add' à la 'sem_num'-ème semaphore du tableau de
//! semaphores 'sems_id' (ajoute 1 par defaut).
bool sem_pv(ipc_id_t sems_id, short unsigned int sem_num, short num_to_add = 1);

//! Protège/execute la fonction 'func' donnée en paramètre avec la 'sem_num'-ème
//! semaphore du tableau de semaphores 'sems_id'.
bool lock(ipc_id_t sems_id, short unsigned int sem_num, const std::function<void(void)>& func);

#endif // PROCESS_UTILS_H
