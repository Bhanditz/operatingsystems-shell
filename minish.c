/* Patrick Watters
   CS350 OS Project 1 Shell
   Sept. 22, 2017
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/resource.h>

// constants
#define MAX_ARGS 16
#define MAX_BUFFER 150
#define DELIMS " \t\r\n\a"

// forward declaration
void removePidShiftList(pid_t pid);

// globals
pid_t pid_list[1000];
int pid_list_index = -1;


void sig_int_handler() 
{
	// kill current process
	pid_t pid = getpid();
	printf(" sig_int_handler\n");

	pid_t newpid = fork();
	
	if (newpid == 0) {
		// char * argv[] = {"./minish"};
		// main(1, argv);
		return;
	} else {
		exit(0);
	}	
}

int runListJobs() 
{
	if (pid_list_index == -1) {
		printf("No background processes running\n");
		return 0;
	}

	int status;
	printf("List of backgrounded processes:\n");

	for (int i = 0; i <= pid_list_index; i++) 
	{
		pid_t ret = waitpid(pid_list[i], &status, WNOHANG);
		printf("Command %d with PID %d", i+1, pid_list[i]);
		if (ret == -1) {
			printf(" Status: ERROR\n");
		} else if (ret == 0) {
			printf(" Status: RUNNING\n");
		} else {
			// remove from list
			printf(" Status: FINISHED\n");
			removePidShiftList(pid_list[i]);
		}
	}
	return 0;
}

void removePidShiftList(pid_t pid)
{
	int remove = -1;

	// find index of process to remove
	for (int i = 0; i <= pid_list_index; i++) {
		if (pid == pid_list[i]) {
			remove = i;
		}
	}
	// iterate from index and shift remaining
	for (int i = remove; i <= pid_list_index; i++) {
		pid_list[i] = pid_list[i+1];
	}

	pid_list_index--;
}

void runExec(char **args, bool background) 
{
	if (args[0] == NULL) return;

	int pid, dupPid;
	int pstatus, cstatus;

	pid = fork();

	switch(pid) 
	{ 	
		case -1: // error
			perror("fork() failed in runExec()\n");
			exit(-1);

		case 0: // child	
			if (execvp(args[0], args) == -1); 
			fclose(stdin); 						// close childs stdin
			fopen("dev/null", "r"); 			// open new empty stdin
			perror(args[0]); 					// execvp shouldn't return unless error
			exit(-1);

		default: // parent
			if (background) {
				pid_list_index++;
				pid_list[pid_list_index] = pid; 
			} else { 
				waitpid(pid, &pstatus, 0);
			}
	}
	return;
}

// Referenced http://brennan.io/2015/01/16/write-a-shell-in-c/ 
char ** parseLine(char *line) 
{
	int buffer = MAX_BUFFER;
	char **args = malloc(buffer * sizeof(char*));
	char *arg;
	int pos = 0;

	if (!args) {
		perror("Mem alloc error - args\n");
		exit(1);
	}

	arg = strtok(line, DELIMS);
	
	while (arg != NULL) {
		args[pos] = arg;
		pos++;

		// check if need more mem
		if (pos >= buffer) {
			buffer += MAX_BUFFER;
			args = realloc(args, buffer * sizeof(char *));
			if (!args) {
				perror("Mem realloc error - args");
				exit(2);
			}
		}
		// get next
		arg = strtok(NULL, DELIMS); 
	}
	// end arr
	args[pos] = NULL; 
	return args;
}

int runShellSpecificCmd(char **args)
{
	if (strcmp(args[0], "cd") == 0) {
		if (chdir(args[1]) != 0) {
			fprintf(stderr, "Error: chdir() to path %s failed\n", args[1]);
		}
	} else {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("Current Directory: %s\n", cwd);
		} else {
			perror("Error: getcwd() failed");
		}
	}
	return 0;
}

// bring background process to foreground
int makeFg(int pid)
{


	return 0;
}

bool isBg(char** args)
{
	int i = 0;
	while(args[i] != NULL) {
		if (strcmp(args[i], "&") == 0) {
			args[i] = NULL;
			return true;
		}
		//printf("%d + %s\n", i, args[i]);
		i++;
	}
	return false;
}

int main(int argc, char** argv)
{
	char **args;
	char *line = NULL;
	char *shellSpecificCmd[] = {"cd", "pwd"};
	pid_t pid;
	size_t buffer = 1024;
	int i = 0;

	while(1)
	{
		printf("shell> ");

		signal(SIGINT, &sig_int_handler); // CTRL-C

		getline(&line, &buffer, stdin);
		args = parseLine(line);

		if (*args[0] == '\r' || *args[0] == '\n') {
			continue;
		}
		else if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) { 
			printf("Exiting Shell\n");
			exit(0);
		}
		else if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "pwd") == 0) {
			runShellSpecificCmd(args);
			continue;
		}
		else if (strcmp(args[0], "listjobs") == 0) {
			runListJobs();
			continue;
		} 
		else if (args[0] != NULL) {
			runExec(args, isBg(args));
		}

		line = NULL;
		args = NULL;
	}

	return 0;
}