#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
int parseline(char* com, char** arg);

int main()
{
	
	int option=0;
	do {
		char *args[1024];
		int child_status;
		int bg;
		pid_t pid;

		char command[1024];

		printf("prompt> ");
		fgets(command, sizeof command, stdin);
		if (strcmp(command, "quit\n") == 0){
			exit(0);
			option = 1;
		}
		else{
			option = 2;
		}


					
				bg = parseline(command, args);

				pid = fork();
				if (pid == 0){
					if(execvp(args[0], args) < 0) {
						printf("failed to open\n");
					}
					
				}
				//	exit(0);
				else if (pid == -1) {
					printf("failed to fork\n");
				}

				if(!bg) {
					if(waitpid(pid, &child_status, 0) < 0) {
						printf("error\n");
					}
				}
				else {
					waitpid(pid, &child_status, WNOHANG); 
					printf("skipped\n");
				}
				
	}
	while(option != 1);

	return 0;
}

int parseline(char* com, char** arg){
	int bg = 0;
	int index = 0;
	char* tok;
        tok  = strtok(com, "  \n");
        arg[index] = tok;
        while((tok = strtok(NULL, "  \n")) != NULL) {
		index++;
		arg[index] = tok;
		printf("%s\n", arg[index]);
	}
	if(strcmp(arg[index], "&") == 0) {
		bg = 1;
		arg[index] = NULL;
	}
	else {
		bg = 0;
	}
	return bg; 
}
