#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int parseline(char* com, char** arg);

void eval() {
	char *args[1024];
	int child_status;
	int bg;
	pid_t pid;

	char command[1024];

	printf("prompt> ");
	fgets(command, sizeof command, stdin);
	if (strcmp(command, "quit\n") == 0){
		exit(0);
	}
	if(strcmp(command, "\n") == 0) {
		return;
	}
	bg = parseline(command, args);
	pid = fork();
	if (pid == 0){
		if(execvp(args[0], args) < 0) {
			char temp[80];
			strcpy(temp, args[0]);
			char str[80];
			strcpy(str, "./");
			strcat(str, args[0]);
			args[0] = str;
			if(execvp(args[0], args) < 0) {
				printf("%s: Command not found.\n", temp);
				exit(0);
			}
		}
	}
	else if (pid == -1) {
		printf("failed to fork\n");
	}
	if(!bg) {
		waitpid(pid, &child_status, 0);
	}
}

int main()
{
	int option=0;
	signal(SIGCHLD, SIG_IGN);
	do {
		eval();	
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
	}
	if(strcmp(arg[index], "&") == 0) {
		bg = 1;
		arg[index] = NULL;
	}
	else {
		arg[index+1] = NULL;
		bg = 0;
	}
	return bg; 
}
