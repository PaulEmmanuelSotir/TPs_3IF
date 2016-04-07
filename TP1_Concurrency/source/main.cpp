#include <string>
#include <stdio.h>
#include <stdlib.h>
#ifndef _MSC_VER
#include <unistd.h>
#include <sys/wait.h> 
#endif
#include <sys/types.h> 
#include <signal.h>
#include <iostream>

#include "process_utils.h"
#include "gestionSortie.h"
#include "gestionEntree.h"
#include "clavier.h"
#include "Outils.h"
#include "Heure.h"
#include "msvc_utils.h"

struct application_tasks
{
	pid_t heure_pid;
	pid_t clavier_pid;
	pid_t porte_gb_pid;
	pid_t porte_bp_autres_pid;
	pid_t porte_bp_profs_pid;
	pid_t porte_sortie_pid;
};

static void quit(application_tasks tasks, int exit_status = EXIT_SUCCESS)
{
	auto kill_task = [&tasks](pid_t task, const std::string& message, signal_t sig = SIGUSR2)
	{
		if(task != -1)
		{
			kill(task, sig);
			Afficher(MESSAGE, message.data());
			waitpid(task, NULL, 0);
		}
	};

	kill_task(tasks.porte_bp_profs_pid, "FIN porte bp profs");
	kill_task(tasks.porte_bp_autres_pid, "FIN porte bp autres");
	kill_task(tasks.porte_gb_pid, "FIN porte gb");
	kill_task(tasks.porte_sortie_pid, "FIN porte sortie");
	kill_task(tasks.heure_pid, "FIN heure");

	TerminerApplication();
	exit(exit_status);
}

static application_tasks init()
{
	application_tasks tasks;
	auto fail_if_bad_pid = [&tasks](pid_t pid)
	{
		if (pid == -1)
			quit(tasks, -1);
	};

	InitialiserApplication(XTERM);

	// Creation de la tache 'heure'
	tasks.heure_pid = ActiverHeure();
	fail_if_bad_pid(tasks.heure_pid);

	// Creation de la tache 'clavier'
	tasks.clavier_pid = activer_clavier();
	fail_if_bad_pid(tasks.clavier_pid);

	// Creation des taches 'gestionEntree' pour chaque barrieres a l'entree
	tasks.porte_gb_pid = ActiverPorteGB();
	fail_if_bad_pid(tasks.porte_gb_pid);
	tasks.porte_bp_profs_pid = ActiverPorteBPProfs();
	fail_if_bad_pid(tasks.porte_bp_profs_pid);
	tasks.porte_bp_autres_pid = ActiverPorteBPAutres();
	fail_if_bad_pid(tasks.porte_bp_autres_pid);

	// Creation de la tache 'gestionSortie'
	tasks.porte_sortie_pid = ActiverPorteSortie();
	fail_if_bad_pid(tasks.porte_sortie_pid);

	return tasks;
}

int main(int argc, char* argv[])
{
	auto tasks = init();
	
	// TODO: enlever ca
	/*Afficher(MESSAGE, (std::string("clavier_pid : ") + std::to_string(tasks.clavier_pid)
		+ " porte_gb_pid : " + std::to_string(tasks.porte_gb_pid)
		+ " heure_pid : " + std::to_string(tasks.heure_pid)
		+ " porte_bp_profs_pid : " + std::to_string(tasks.porte_bp_profs_pid)
		+ " porte_sortie_pid : " + std::to_string(tasks.porte_sortie_pid)
		+ " porte_bp_autres_pid : " + std::to_string(tasks.porte_bp_autres_pid)).data());*/

	// Attente de la fin de la tache clavier
	waitpid(tasks.clavier_pid, NULL, 0); //TODO: essayer nullptr

	quit(tasks);
}

