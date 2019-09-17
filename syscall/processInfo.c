#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include "processInfo.h"

asmlinkage long sys_listProcessInfo(long pid, const char __user *buf, int size) {
struct task_struct *proces;
unsigned char kbuf[256];
int bufsz;
int ret;

int index = 0;

	/* Find the process */
	for_each_process(proces) {
		if( (long)task_pid_nr(proces) == pid){
			/* Print the process info to the buffer */
			snprintf(kbuf, sizeof(kbuf), "Process: %s\n PID_Number: %ld\n Process State: %ld\n Priority: %ld\n RT_Priority: %ld\n Static Priority: %ld\n Normal Priority: %ld\n", 
					proces->comm, 
					(long)task_pid_nr(proces), 
					(long)proces->state, 
					(long)proces->prio, 
					(long)proces->rt_priority, 
					(long)proces->static_prio, (long)proces->normal_prio);
			bufsz = strlen(kbuf)+1;

			/* User buffer is too small */
			if(bufsz > size){
				return -1;
			}

			/* success */
			//ret = copy_to_user((void*)buf, (void*)kbuf, bufsz);

			//return bufsz - ret;
		}
	}

	// desafio 1
	for_each_process(proces) {
		if ( (long)proces->state != TASK_RUNNING) {
			kbuf[index] = (long)task_pid_nr(proces);
			index++;


		}


	}

	// quantidade de posicoes que coloquei vezes long
	bufsz = index * sizeof(long);

	/* success */
	ret = copy_to_user((void*)buf, (void*)kbuf, bufsz);

	//return bufsz - ret; 

	// retorna quantas posicoes foram preenchidas
	return index;	// desafio 1

/* Process not found */
return -2;	
}
