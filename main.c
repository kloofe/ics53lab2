#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	char fullCommand[80];
	char *tok;
	int option=0;
	int child_status;
	bool bg;
	pid_t pid;
	do {
		char command[80];

		printf("prompt> ");
		fgets(command, sizeof command, stdin);

		if (strcmp(command, "quit\n") == 0){
			option = 1;
		}
		else{
			option = 2;
		}


		switch(option){
			case 1:
				break;
			case 2:
				printf("");
				int index;
				char** args = malloc(sizeof(char)*250);
				index = 0;
				tok  = strtok(command, "  \n");
				args[index] = tok;
				while((tok = strtok(NULL, "  \n")) != NULL) {
					index++;
					args[index] = tok;
					printf("%s\n", args[index]);
				}
				printf("%s\n", args[index]);
				if(strcmp(args[index], "&") == 0) {
					printf("cry\n");
					bg = true;
					args[index] = NULL;
				}
				else {
					bg = false;
				}

				pid = fork();
				if (pid == 0){
						
					if(execvp(args[0], args) < 0) {
							printf("failed to start exc\n");
					}
					
					
				
					free(args);	
					//exit(0);
				}
				else if(pid == -1) {
					printf("failed\n");
				}
				else{
					if(!bg) {
					waitpid(pid, &child_status, 0);
					}
					else {
						waitpid(pid, &child_status, WNOHANG);
					}
					if(WIFEXITED(child_status)) {
						printf("Child terminated\n");
					}
				}
				break;
			
		}
	}
	while(option != 1);

	return 0;
}
