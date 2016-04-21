#include <stdio.h>
//#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	char fullCommand[80];
	char command[80];
	char* arg = malloc(sizeof(char)*250);
	int option=0;
	int child_status;
	pid_t pid;
	do {
		printf("prompt> ");
		fgets(command, sizeof command, stdin);
		strcpy(arg, command);
		

		if (strcmp(command, "quit") == 0){
			option = 1;
		}
		else{
			option = 2;
		}

		switch(option){
			case 1:
				break;
			case 2:
				pid = fork();
				if (pid == 0){
					printf("child\n");
					if(execvp(command, args) < 0) {
						printf("failed\n");
					}
					//exit(0);
				}
				else if(pid == -1) {
					printf("failed\n");
				}
				else{
					waitpid(0, &child_status, 0);
					if(WIFEXITED(child_status)) {
						printf("Child terminated\n");
					}
					printf("parent\n");
				}
				break;
			
		}
	}
	while(option == 3 && option == 1);

	return 0;
}
