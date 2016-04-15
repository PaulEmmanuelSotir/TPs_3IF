/*************************************************************************
			Process utils - aide a la manipulation de processus
			---------------------------------------------------
	debut   			 : 20/03/2016
	binome               : B3330
*************************************************************************/

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include systeme
#include <string>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <mqueue.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <functional>
#include <sys/types.h>

//------------------------------------------------------ Include personnel
#include "process_utils.h"
#include "Outils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------ Fonctions privees
namespace
{
	bool create_or_open_message_queue(ipc_id_t& msqid, int id, int perm, std::string path, int flags)
	{
		key_t key = ftok(path.data(), id);
		if (key == -1)
			return false;
		msqid = msgget(key, perm | flags);
		return msqid >= 0;
	}
}

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

bool open_message_queue(ipc_id_t& msqid, int id, int permission, std::string path)
{
	return create_or_open_message_queue(msqid, id, permission, path, 0);
}

bool create_message_queue(ipc_id_t& msqid, int id, int permission, std::string path, bool fail_if_exist)
{
	return create_or_open_message_queue(msqid, id, permission, path, fail_if_exist ? (IPC_CREAT | IPC_EXCL) : IPC_CREAT);
}

bool delete_message_queue(ipc_id_t msqid)
{
	return msgctl(msqid, IPC_RMID, nullptr) != -1;
}

bool delete_shared_memory(ipc_id_t id)
{
	return (shmctl(id, IPC_RMID, nullptr) != -1);
}

bool sem_pv(ipc_id_t sems_id, short unsigned int sem_num, short num_to_add)
{
	sembuf sem_buf{ sem_num, num_to_add, 0 };
	int rslt = 0;

	do { rslt = semop(sems_id, &sem_buf, 1); } while (rslt == -1 && errno == EINTR);

	return rslt >= 0;
}

bool lock(ipc_id_t sems_id, short unsigned int sem_num, const std::function<void(void)>& func)
{
	// Decremente la semaphore
	if (!sem_pv(sems_id, sem_num, -1))
		return false;

	// Execute le code protégé par la semaphore
	func();

	// Incremente la semaphore
	return sem_pv(sems_id, sem_num, 1);
}
