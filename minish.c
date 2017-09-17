/* Patrick Watters
   CS350 OS Project 1 Shell
   Sept. 22, 2017
*/

#include <sys/resource.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ARGS 16
#define MAX_BUFFER 512


int main(int argc, char** argv)
{
	char buffer[MAX_BUFFER];
	char *args[MAX_ARGS];
	char *line;
	int pid;

	while(1)
	{
	

		switch(pid = fork()) 
		{ 	
			case -1:
				perror("fork");
				break;
			case 0:
				doexec();
				break;
			default:
				waitpid(pid, NULL, 0);
				break;
		}
	}
	return 0;
}
